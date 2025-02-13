/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:18:25 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/13 18:20:56 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_correct(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!ft_is_uint(args[i]))
			return (0);
		i++;
	}
	return (1);
}
