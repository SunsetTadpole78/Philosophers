/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:48:17 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/19 09:53:39 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestramp(void)
{
	struct timeval	t;
	long			time;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000 + t.tv_usec / 1000);
	return (time);
}

long	simulation_timestramp(t_simulation *simulation)
{
	return (timestramp() - simulation->start_time);
}

void	ft_usleep(int ms)
{
	long	finish;
	long	actual;

	actual = timestramp();
	finish = actual + ms;
	while (actual < finish)
	{
		actual = timestramp();
		usleep(1);
	}
}

long	get_start_time(t_simulation *simulation)
{
	long	v;

	lock_mutex(START_TIME, 0);
	v = simulation->start_time;
	unlock_mutex(START_TIME, 0);
	return (v);
}
