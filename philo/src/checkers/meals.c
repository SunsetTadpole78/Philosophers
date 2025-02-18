/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:59:01 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/18 09:59:02 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_min_meals_count(t_simulation *simulation)
{
	int	v;

	lock_mutex(MEALS_COUNT, 0);
	v = simulation->min_meals_count;
	unlock_mutex(MEALS_COUNT, 0);
	return (v);
}

static int	get_meals_count(t_philosopher *thomas)
{
	int	v;

	lock_mutex(MEALS_COUNT, 0);
	v = thomas->meals_count;
	unlock_mutex(MEALS_COUNT, 0);
	return (v);
}

static void	add_meal(t_philosopher *thomas)
{
	lock_mutex(MEALS_COUNT, 0);
	thomas->meals_count++;
	unlock_mutex(MEALS_COUNT, 0);
}

void	check_meals(t_philosopher *thomas)
{
	t_philosopher	*other_thomas;
	int				min;

	min = get_min_meals_count(thomas->simulation);
	if (min == -1)
		return ;
	add_meal(thomas);
	if (get_meals_count(thomas) < min)
		return ;
	other_thomas = thomas->next;
	while (other_thomas->id != thomas->id)
	{
		if (get_meals_count(other_thomas) < min)
			return ;
		other_thomas = other_thomas->next;
	}
	lock_mutex(STOP, 0);
	thomas->simulation->stop = 1;
	unlock_mutex(STOP, 0);
}
