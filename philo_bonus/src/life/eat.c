/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:46:38 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/16 23:16:11 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	eat(t_philosopher *thomas)
{
	long	time;

	sem_wait(thomas->simulation->last_eat_sem);
	thomas->last_eat = timestamp();
	sem_post(thomas->simulation->last_eat_sem);
	time = timestamp();
	if (!safe_display("is eating", thomas, 0))
		return (0);
	while (time < (thomas->last_eat + thomas->simulation->time_to_eat))
	{
		if (is_stop(thomas))
			return (0);
		usleep(1);
		time = timestamp();
	}
	return (1);
}
