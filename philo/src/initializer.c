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

t_philosopher	*create_philosopher(int id, t_simulation *simulation,
	t_philosopher *old)
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
	thomas->simulation = simulation;
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

static void	create_philosophers(t_simulation *simulation)
{
	int				i;
	t_philosopher	*cur;

	simulation->first = create_philosopher(1, simulation, NULL);
	i = 1;
	cur = simulation->first;
	while (i < simulation->count)
	{
		cur->next = create_philosopher(i + 1, simulation, cur);
		i++;
		cur = cur->next;
	}
	cur->next = simulation->first;
	cur->right_fork = simulation->first->left_fork;
}

t_simulation	*init_simulation(char **argv)
{
	t_simulation	*simulation;

	simulation = malloc(sizeof(t_simulation));
	if (!simulation)
		return (NULL);
	simulation->count = ft_atoi(argv[0]);
	simulation->time_to_die = ft_atoi(argv[1]);
	simulation->time_to_eat = ft_atoi(argv[2]);
	simulation->time_to_sleep = ft_atoi(argv[3]);
	simulation->min_meals_count = -1;
	if (argv[4])
		simulation->min_meals_count = ft_atoi(argv[4]);
	simulation->start_time = -1;
	simulation->stop = 0;
	register_mutexs();
	create_philosophers(simulation);
	return (simulation);
}
