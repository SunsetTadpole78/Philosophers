/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:38:37 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/16 23:27:02 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	go_sleep(t_philosopher *thomas)
{
	long	time;
	long	wake_up;

	wake_up = timestamp() + thomas->simulation->time_to_sleep;
	time = timestamp();
	if (!safe_display("is sleeping", thomas, 0))
		return (0);
	while (time < wake_up)
	{
		if (is_stop(thomas))
			return (0);
		usleep(1);
		time = timestamp();
	}
	return (1);
}
