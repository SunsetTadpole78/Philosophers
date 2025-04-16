/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:51:29 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/17 01:05:37 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_meals(void *args)
{
	t_simulation	*simulation;
	int			i;

	simulation = (t_simulation *)args;
	i = 0;
	while (i++ < simulation->count)
		sem_wait(simulation->meals_sem);
	sem_post(simulation->stop_sem);
	return (NULL);
}


void	start_meals_checker(t_simulation *simulation)
{
	pthread_create(&simulation->meals, NULL, check_meals, simulation);
	pthread_join(simulation->meals, NULL);
}
