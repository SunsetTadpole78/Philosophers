/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:59:14 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/18 09:59:15 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	rip(t_philosopher *thomas)
{
	if (is_stop(thomas->simulation))
		return ;
	lock_mutex(STOP, 0);
	thomas->simulation->stop = 1;
	unlock_mutex(STOP, 0);
	safe_display("died", thomas, 1);
}
