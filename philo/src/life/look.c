/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:59:21 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/18 09:59:22 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	look_spaghetti_bowl(t_philosopher *thomas)
{
	while (!is_dead(thomas))
		usleep(1);
}
