/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:24:37 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/17 02:21:50 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_simulation	*simulation;
	int				i;

	if ((argc != 5 && argc != 6) || !is_correct(argv + 1))
	{
		invalid_arguments(argv);
		return (1);
	}
	simulation = init_simulation(argv + 1);
	if (!simulation)
	{
		write(2, "Malloc error\n", 13);
		return (2);
	}
	start_simulation(simulation);
	pthread_create(&simulation->meals, NULL, check_meals, simulation);
	i = 0;
	while (i++ < simulation->count)
		waitpid(-1, NULL, 0);
	pthread_join(simulation->meals, NULL);
	free_simulation(simulation);
	return (0);
}
