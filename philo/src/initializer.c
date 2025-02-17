/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:01:27 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/17 17:27:23 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philosopher	*create_philosopher(int id, t_game *game, t_philosopher *old)
{
	t_philosopher	*thomas;

	thomas = malloc(sizeof(t_philosopher));
	if (!thomas)
		return (NULL);
	thomas->id = id;
	thomas->left_fork = register_mutex(FORK, id);
	thomas->right_fork = NULL;
	thomas->last_eat = -1;
	thomas->last_sleep = -1;
	thomas->meals_count = 0;
	thomas->game = game;
	if (old)
		old->right_fork = thomas->left_fork;
	register_mutex(LAST_EAT, id);
	register_mutex(LAST_SLEEP, id);
	return (thomas);
}

static void	register_mutexs(void)
{
	register_mutex(START_TIME, 0);
	register_mutex(PRINT_F, 0);
	register_mutex(TIME_TO_DIE, 0);
	register_mutex(TIME_TO_EAT, 0);
	register_mutex(MEALS_COUNT, 0);
	register_mutex(STOP, 0);
	register_mutex(COUNT, 0);
}

static void	create_philosophers(t_game *game)
{
	int				i;
	t_philosopher	*cur;

	game->first = create_philosopher(1, game, NULL);
	i = 1;
	cur = game->first;
	while (i < game->count)
	{
		cur->next = create_philosopher(i + 1, game, cur);
		i++;
		cur = cur->next;
	}
	cur->next = game->first;
	cur->right_fork = game->first->left_fork;
}

t_game	*init_game(char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->count = ft_atoi(argv[0]);
	game->time_to_die = ft_atoi(argv[1]);
	game->time_to_eat = ft_atoi(argv[2]);
	game->time_to_sleep = ft_atoi(argv[3]);
	game->min_meals_count = -1;
	if (argv[4])
		game->min_meals_count = ft_atoi(argv[4]);
	game->start_time = -1;
	game->stop = 0;
	register_mutexs();
	create_philosophers(game);
	return (game);
}
