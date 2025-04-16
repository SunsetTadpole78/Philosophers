/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:59:07 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/16 12:58:57 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philosopher *thomas)
{
	long	time;

	if (is_stop(thomas->simulation))
		return (1);
	time = get_last_eat(thomas);
	if (time == -1)
		time = get_start_time(thomas->simulation);
	else
		time -= get_time_to_eat(thomas->simulation);
	if (timestramp() - time > get_time_to_die(thomas->simulation))
	{
		rip(thomas);
		return (1);
	}
	return (0);
}
