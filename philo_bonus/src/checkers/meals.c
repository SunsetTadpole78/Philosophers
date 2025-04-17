/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:51:29 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/17 02:27:27 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	add_meal(t_philosopher *thomas)
{
	int	v;

	sem_wait(thomas->simulation->meals_check_sem);
	thomas->meals_count++;
	v = thomas->meals_count;
	sem_post(thomas->simulation->meals_check_sem);
	if (v == thomas->simulation->min_meals_count)
		sem_post(thomas->simulation->meals_sem);
}

void	*check_meals(void *args)
{
	t_simulation	*simulation;
	int				i;

	simulation = (t_simulation *)args;
	if (simulation->min_meals_count <= 0)
		return (NULL);
	i = 0;
	while (i < simulation->count)
	{
		sem_wait(simulation->meals_sem);
		i++;
	}
	sem_post(simulation->stop_sem);
	return (NULL);
}
