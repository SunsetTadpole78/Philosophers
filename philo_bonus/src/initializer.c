/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:01:27 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/17 00:58:46 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_philosopher	*create_philosopher(int id, t_simulation *simulation)
{
	t_philosopher	*thomas;

	thomas = malloc(sizeof(t_philosopher));
	if (!thomas)
		return (NULL);
	thomas->id = id;
	thomas->last_eat = -1;
	thomas->meals_count = 0;
	thomas->dead = 0;
	thomas->stop = 0;
	thomas->started = 0;
	thomas->simulation = simulation;
	return (thomas);
}

static void	create_philosophers(t_simulation *simulation)
{
	int				i;
	t_philosopher	*cur;

	simulation->first = create_philosopher(1, simulation);
	i = 1;
	cur = simulation->first;
	while (i < simulation->count)
	{
		cur->next = create_philosopher(i + 1, simulation);
		i++;
		cur = cur->next;
	}
	cur->next = simulation->first;
}

static void	init_semaphores(t_simulation *simulation)
{
	simulation->last_eat_sem = sem_open("/last_eat", O_CREAT, 0600, 1);
	simulation->stop_sem = sem_open("/stop", O_CREAT, 0600, 1);
	simulation->check_stop_sem = sem_open("/check_stop", O_CREAT, 0600, 1);
	simulation->print_sem = sem_open("/print", O_CREAT, 0600, 1);
	simulation->forks_sem = sem_open("/forks", O_CREAT, 0600,
			simulation->count);
	simulation->deadlock_sem = sem_open("/deadlock", O_CREAT, 0600, 1);
	simulation->started_sem = sem_open("/started", O_CREAT, 0600, 1);
	simulation->meals_sem = sem_open("/meals", O_CREAT, 0600, 1);
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
	create_philosophers(simulation);
	unlink_semaphores();
	init_semaphores(simulation);
	return (simulation);
}
