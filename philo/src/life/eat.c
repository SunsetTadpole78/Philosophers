/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:39:40 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/18 09:44:08 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_last_eat(t_philosopher *thomas)
{
	long	v;

	lock_mutex(LAST_EAT, thomas->id);
	v = thomas->last_eat;
	unlock_mutex(LAST_EAT, thomas->id);
	return (v);
}

static void	set_last_eat(t_philosopher *thomas)
{
	lock_mutex(LAST_EAT, thomas->id);
	thomas->last_eat = timestramp() + (thomas->simulation->time_to_eat);
	unlock_mutex(LAST_EAT, thomas->id);
}

void	eat(t_philosopher *thomas)
{
	if (is_dead(thomas))
		return ;
	set_last_eat(thomas);
	safe_display("is eating", thomas, 0);
	while (timestramp() < get_last_eat(thomas))
	{
		if (check_others(thomas))
			return ;
		usleep(1);
	}
}
