/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:05:56 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/16 11:17:24 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_simulation(t_simulation *simulation)
{
	int				i;
	t_philosopher	*cur;
	t_philosopher	*tmp;

	i = 0;
	cur = simulation->first;
	while (i < simulation->count)
	{
		pthread_join(cur->thread, NULL);
		cur = cur->next;
		i++;
	}
	i = 0;
	cur = simulation->first;
	while (i < simulation->count)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp);
		i++;
	}
	destroy_mutexs();
	free(simulation);
}
