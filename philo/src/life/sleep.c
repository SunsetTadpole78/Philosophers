/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:44:30 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/18 09:44:31 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	get_last_sleep(t_philosopher *thomas)
{
	long	v;

	lock_mutex(LAST_SLEEP, thomas->id);
	v = thomas->last_sleep;
	unlock_mutex(LAST_SLEEP, thomas->id);
	return (v);
}

static void	set_last_sleep(t_philosopher *thomas)
{
	lock_mutex(LAST_SLEEP, thomas->id);
	thomas->last_sleep = timestramp() + (thomas->simulation->time_to_sleep);
	unlock_mutex(LAST_SLEEP, thomas->id);
}

void	go_sleep(t_philosopher *thomas)
{
	if (is_dead(thomas))
		return ;
	set_last_sleep(thomas);
	safe_display("is sleeping", thomas, 0);
	while (timestramp() < get_last_sleep(thomas))
	{
		if (is_dead(thomas))
			return ;
		if (check_others(thomas))
			return ;
		usleep(1);
	}
}
