/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:59:07 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/17 01:39:01 by lroussel         ###   ########.fr       */
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

static long	get_last_eat(t_philosopher *thomas)
{
	long	v;

	sem_wait(thomas->simulation->last_eat_sem);
	v = thomas->last_eat;
	sem_post(thomas->simulation->last_eat_sem);
	return (v);
}

static int	on_death(t_philosopher *thomas)
{
	if (thomas->simulation->min_meals_count > 0)
		sem_post(thomas->simulation->meals_sem);
	sem_wait(thomas->simulation->print_sem);
	if (is_stop(thomas))
	{
		sem_post(thomas->simulation->print_sem);
		return (0);
	}
	printf("%li %i died\n",
		simulation_timestamp(thomas->simulation), thomas->id);
	sem_post(thomas->simulation->stop_sem);
	sem_wait(thomas->simulation->check_stop_sem);
	thomas->dead = 1;
	sem_post(thomas->simulation->check_stop_sem);
	sem_post(thomas->simulation->stop_sem);
	usleep(50000);
	sem_post(thomas->simulation->print_sem);
	return (1);
}

void	*check_death(void *args)
{
	t_philosopher	*thomas;

	thomas = (t_philosopher *)args;
	while (1)
	{
		if (is_stop(thomas))
			return (NULL);
		if (timestamp() > (get_last_eat(thomas)
				+ thomas->simulation->time_to_die))
		{
			if (!on_death(thomas))
				return (NULL);
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
