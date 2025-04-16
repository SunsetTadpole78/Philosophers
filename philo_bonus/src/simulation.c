/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:04:41 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/17 00:21:54 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_stop(t_philosopher *thomas)
{
	int	v;
	
	sem_wait(thomas->simulation->check_stop_sem);
	v = thomas->stop || thomas->dead;
	sem_post(thomas->simulation->check_stop_sem);
	return (v);
}

long	get_last_eat(t_philosopher *thomas)
{
	long	v;

	sem_wait(thomas->simulation->last_eat_sem);
	v = thomas->last_eat;
	sem_post(thomas->simulation->last_eat_sem);
	return (v);
}

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
	int		res;
	
	thomas = (t_philosopher *)args;

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
		drop_forks(thomas);
		if (!res || !go_sleep(thomas))
			break ;
	}
	return (NULL);
}

void	*check_death(void *args)
{
	t_philosopher	*thomas;
	
	thomas = (t_philosopher *)args;
	while (1)
	{
		if (is_stop(thomas))
			return (NULL);
		if (timestamp() > (get_last_eat(thomas) + thomas->simulation->time_to_die))
		{
			sem_wait(thomas->simulation->print_sem);
			if (is_stop(thomas))
			{
				sem_post(thomas->simulation->print_sem);
				return (NULL);
			}
			printf("%li %i dead\n", simulation_timestamp(thomas->simulation), thomas->id);
			sem_post(thomas->simulation->stop_sem);
			sem_wait(thomas->simulation->check_stop_sem);
			thomas->dead = 1;
			sem_post(thomas->simulation->check_stop_sem);
			sem_post(thomas->simulation->stop_sem);
			usleep(500);
			sem_post(thomas->simulation->print_sem);
		}
		usleep(1);
	}
	return (NULL);
}

void	on_one_dead(t_philosopher *thomas)
{
	sem_wait(thomas->simulation->stop_sem);
	sem_post(thomas->simulation->stop_sem);

	sem_wait(thomas->simulation->check_stop_sem);
	thomas->stop = 1;
	sem_post(thomas->simulation->check_stop_sem);
}

void	start_simulation(t_simulation *simulation)
{
	t_philosopher	*cur;
	pid_t	pid;
	int	i;

	cur = simulation->first;
	i = 0;
	while (i < simulation->count)
	{
		pid = fork();
		if (pid == 0)
		{
			if (cur->id == 1)
			{
				sem_wait(simulation->stop_sem); //ty gakarbou
				sem_wait(cur->simulation->deadlock_sem);
			}
			else
			{
				sem_wait(cur->simulation->deadlock_sem);
				sem_post(cur->simulation->deadlock_sem);
				set_started(cur);
			}
			simulation->start_time = timestamp();
			cur->last_eat = simulation->start_time;
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
	i = 0;
	while (i++ < simulation->count)
		wait(NULL);
}
