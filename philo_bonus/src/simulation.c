/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:04:41 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/17 10:04:52 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_started(t_philosopher *thomas)
{
	sem_wait(thomas->simulation->started_sem);
	thomas->started = 1;
	sem_post(thomas->simulation->started_sem);
}

int	is_started(t_philosopher *thomas)
{
	int	v;

	sem_wait(thomas->simulation->started_sem);
	v = thomas->started;
	sem_post(thomas->simulation->started_sem);
	return (v);
}

void	*life(void *args)
{
	t_philosopher	*thomas;
	int				res;

	thomas = (t_philosopher *)args;
	if (thomas->id % 2 == 1)
		usleep(500);
	while (1)
	{
		if (!think(thomas))
			break ;
		if (!take_forks(thomas))
			break ;
		if (thomas->id == 1 && !is_started(thomas))
		{
			set_started(thomas);
			sem_post(thomas->simulation->deadlock_sem);
		}
		res = eat(thomas);
		if (thomas->simulation->min_meals_count > 0)
			add_meal(thomas);
		drop_forks(thomas);
		if (!res || !go_sleep(thomas))
			break ;
	}
	return (NULL);
}

static void	init_life(t_simulation *simulation, t_philosopher *thomas)
{
	if (thomas->simulation->min_meals_count > 0)
		sem_wait(simulation->meals_sem);
	thomas->last_eat = simulation->start_time;
	if (thomas->id == 1)
	{
		sem_wait(simulation->stop_sem);
		sem_wait(simulation->deadlock_sem);
	}
	else
	{
		sem_wait(simulation->deadlock_sem);
		sem_post(simulation->deadlock_sem);
		set_started(thomas);
	}
}

void	start_simulation(t_simulation *simulation)
{
	t_philosopher	*cur;
	pid_t			pid;
	int				i;

	simulation->start_time = timestamp();
	cur = simulation->first;
	i = 0;
	while (i < simulation->count)
	{
		pid = fork();
		if (pid == 0)
		{
			init_life(simulation, cur);
			pthread_create(&cur->life, NULL, life, cur);
			pthread_create(&cur->check_death, NULL, check_death, cur);
			on_one_dead(cur);
			pthread_join(cur->life, NULL);
			pthread_join(cur->check_death, NULL);
			free_simulation(simulation);
			exit(0);
		}
		i++;
		cur = cur->next;
	}
}
