/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:01:27 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/13 18:15:52 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*create_fork(int philosopher_id)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->philosopher_id = philosopher_id;
	fork->is_used = 0;
	return (fork);
}

t_philosopher	*create_philosopher(int id, t_fork *his_fork, t_philosopher *old)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->id = id;
	philosopher->left_fork = his_fork;
	philosopher->alive = 1;
	philosopher->is_eating = 0;
	philosopher->is_thinking = 0;
	philosopher->is_sleeping = 0;
	if (old)
		old->right_fork = his_fork;
	return (philosopher);
}

t_game	*init_game(char **argv)
{
	t_game	*game;
	int		i;
	t_philosopher	*cur;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->count = ft_atoi(argv[0]);
	game->forks = malloc(sizeof(t_fork *) * (game->count + 1));
	game->forks[0] = create_fork(1);
	game->first = create_philosopher(1, game->forks[0], NULL);
	if (!game->first)
	{
		//TODO
		return (NULL);
	}
	i = 1;
	cur = game->first;
	while (i < game->count)
	{
		game->forks[i - 1] = create_fork(i + 1);
		cur->next = create_philosopher(i + 1, game->forks[i - 1], cur);
		i++;
		cur = cur->next;
	}
	cur->next = game->first;
	cur->right_fork = game->first->left_fork;
	cur = game->first;
	return (game);
}
