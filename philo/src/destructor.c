/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:05:56 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/13 18:16:41 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_game(t_game *game)
{
	int			i;
	t_philosopher	*cur;
	t_philosopher	*tmp;

	i = 0;
	cur = game->first;
	while (i < game->count)
	{
		//printf("%i %p {%p %p} %p\n", cur->id, cur, cur->left_fork, cur->right_fork, cur->next);
		free(cur->left_fork);
		tmp = cur;
		cur = cur->next;
		free(tmp);
		i++;
	}
	free(game->forks);
	free(game);
}
