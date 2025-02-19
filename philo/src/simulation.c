/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:15:30 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/19 09:30:10 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_stop(t_simulation *simulation)
{
	int	v;

	lock_mutex(STOP, 0);
	v = simulation->stop;
	unlock_mutex(STOP, 0);
	return (v);
}

void	*life(void *args)
{
	t_philosopher	*thomas;
	int				unlock_forks;

	thomas = (t_philosopher *)args;
	if (thomas->id % 2 == 1)
		ft_usleep(50);
	lock_mutex(START_TIME, 0);
	if (thomas->simulation->start_time == -1)
		thomas->simulation->start_time = timestramp();
	unlock_mutex(START_TIME, 0);
	while (!is_dead(thomas))
	{
		think(thomas);
		unlock_forks = take_forks(thomas);
		eat(thomas);
		check_meals(thomas);
		if (unlock_forks)
			drop_forks(thomas);
		go_sleep(thomas);
	}
	return (args);
}

int	start_simulation(t_simulation *simulation)
{
	t_philosopher	*cur;

	cur = simulation->first;
	while (cur)
	{
		pthread_create(&cur->thread, NULL, life, cur);
		cur = cur->next;
		if (cur->id == 1)
			break ;
	}
	return (1);
}
