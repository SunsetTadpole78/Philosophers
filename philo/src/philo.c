/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:24:37 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/13 18:28:31 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if ((argc != 5 && argc != 6) || !is_correct(argv + 1))
	{
		write(2, argv[0], ft_strlen(argv[0]));
		write(2 , " <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n", 114);
		return (1);
	}
	game = init_game(argv + 1);
	if (!game)
	{
		write(2, "Malloc error\n", 13);
		return (2);
	}
	free_game(game);
	return (0);
}
