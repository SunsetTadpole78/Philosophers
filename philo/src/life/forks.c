/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:48:29 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/18 09:48:32 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	thomas_count(t_simulation *simulation)
{
	int	v;

	lock_mutex(COUNT, 0);
	v = simulation->count;
	unlock_mutex(COUNT, 0);
	return (v);
}

static int	take_fork(t_philosopher *thomas, int id, int other_id)
{
	lock_mutex(FORK, id);
	if (is_dead(thomas))
	{
		unlock_mutex(FORK, id);
		if (other_id != -1)
			unlock_mutex(FORK, other_id);
		return (0);
	}
	safe_display("has taken a fork", thomas, 0);
	if (thomas_count(thomas->simulation) == 1)
	{
		unlock_mutex(FORK, id);
		look_spaghetti_bowl(thomas);
		return (0);
	}
	return (1);
}

int	take_forks(t_philosopher *thomas)
{
	if (is_dead(thomas))
		return (0);
	if (thomas->id % 2 == 0)
	{
		if (!take_fork(thomas, thomas->right_fork->variant, -1))
			return (0);
		if (!take_fork(thomas, thomas->left_fork->variant,
				thomas->right_fork->variant))
			return (0);
	}
	else
	{
		if (!take_fork(thomas, thomas->left_fork->variant, -1))
			return (0);
		if (!take_fork(thomas, thomas->right_fork->variant,
				thomas->left_fork->variant))
			return (0);
	}
	return (1);
}

void	drop_forks(t_philosopher *thomas)
{
	unlock_mutex(FORK, thomas->id);
	unlock_mutex(FORK, thomas->next->id);
}
