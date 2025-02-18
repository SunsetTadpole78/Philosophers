/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:08:36 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/18 09:16:00 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	invalid_arguments(char **argv)
{
	write(2, "\033[0;33m", 7);
	write(2, "Usage: ", 7);
	write(2, "\033[0;31m", 7);
	write(2, argv[0], ft_strlen(argv[0]));
	write(2, " <number_of_philosophers> <time_to_die> <time_to_eat> ", 53);
	write(2, "<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n",
		60);
	write(2, "\033[0m", 5);
}
