/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:48:17 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/16 20:47:02 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	timestamp(void)
{
	struct timeval	t;
	long			time;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000 + t.tv_usec / 1000);
	return (time);
}

long	simulation_timestamp(t_simulation *simulation)
{
	return (timestamp() - simulation->start_time);
}

void	ft_usleep(int ms)
{
	long	finish;
	long	actual;

	actual = timestamp();
	finish = actual + ms;
	while (actual < finish)
	{
		actual = timestamp();
		usleep(1);
	}
}
