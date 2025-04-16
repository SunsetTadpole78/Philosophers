/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:05:56 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/17 00:59:25 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	close_semaphores(t_simulation *simulation)
{
	sem_close(simulation->last_eat_sem);
	sem_close(simulation->stop_sem);
	sem_close(simulation->check_stop_sem);
	sem_close(simulation->print_sem);
	sem_close(simulation->forks_sem);
	sem_close(simulation->deadlock_sem);
	sem_close(simulation->started_sem);
	sem_close(simulation->meals_sem);
}

void	free_simulation(t_simulation *simulation)
{
	int				i;
	t_philosopher	*cur;
	t_philosopher	*tmp;

	close_semaphores(simulation);
	i = 0;
	cur = simulation->first;
	while (i < simulation->count)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp);
		i++;
	}
	free(simulation);
}

void	unlink_semaphores(void)
{
	sem_unlink("/last_eat");
	sem_unlink("/stop");
	sem_unlink("/check_stop");
	sem_unlink("/print");
	sem_unlink("/forks");
	sem_unlink("/deadlock");
	sem_unlink("/started");
	sem_unlink("/meals");
}
