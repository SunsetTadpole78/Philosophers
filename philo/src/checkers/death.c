/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:59:07 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/18 09:59:08 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_time_to_die(t_simulation *simulation)
{
	int	v;

	lock_mutex(TIME_TO_DIE, 0);
	v = simulation->time_to_die;
	unlock_mutex(TIME_TO_DIE, 0);
	return (v);
}

static int	get_time_to_eat(t_simulation *simulation)
{
	int	v;

	lock_mutex(TIME_TO_EAT, 0);
	v = simulation->time_to_eat;
	unlock_mutex(TIME_TO_EAT, 0);
	return (v);
}

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

int	check_others(t_philosopher *thomas)
{
	t_philosopher	*other_thomas;

	other_thomas = thomas->next;
	while (other_thomas->id != thomas->id)
	{
		if (is_dead(other_thomas))
			return (1);
		other_thomas = other_thomas->next;
	}
	return (0);
}
