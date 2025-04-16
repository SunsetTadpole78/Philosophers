/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:12:19 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/16 23:50:12 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	take_forks(t_philosopher *thomas)
{
	sem_wait(thomas->simulation->forks_sem);
	safe_display("has taken a fork", thomas, 0);
	if (is_stop(thomas))
	{
		sem_post(thomas->simulation->forks_sem);
		return (0);
	}
	sem_wait(thomas->simulation->forks_sem);
	safe_display("has taken a fork", thomas, 0);
	if (is_stop(thomas))
	{
		drop_forks(thomas);
		return (0);
	}
	return (1);
}

void	drop_forks(t_philosopher *thomas)
{
	(void)thomas;
	sem_post(thomas->simulation->forks_sem);
	sem_post(thomas->simulation->forks_sem);
}
