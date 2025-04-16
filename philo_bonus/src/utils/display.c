/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:48:20 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/17 00:30:50 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	safe_display(char *message, t_philosopher *thomas, int exception)
{
	int	stop;

	sem_wait(thomas->simulation->print_sem);
	stop = is_stop(thomas);
	if (exception || !stop)
		printf("%li %i %s\n", simulation_timestamp(thomas->simulation),
			thomas->id, message);
	sem_post(thomas->simulation->print_sem);
	return (!stop);
}
