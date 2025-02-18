/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:48:20 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/18 09:48:24 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_display(char *message, t_philosopher *thomas, int exception)
{
	lock_mutex(PRINT_F, 0);
	if (exception || !is_stop(thomas->simulation))
		printf("%li %i %s\n", simulation_timestramp(thomas->simulation),
			thomas->id, message);
	unlock_mutex(PRINT_F, 0);
}
