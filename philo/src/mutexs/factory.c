/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:18:18 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/18 18:15:15 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_mutexs	*mutexs(void)
{
	static t_mutexs	*m = NULL;

	if (!m)
	{
		m = malloc(sizeof(t_mutexs));
		m->mutexs = malloc(sizeof(t_mutex *));
		m->mutexs[0] = NULL;
		m->count = 0;
	}
	return (m);
}

t_mutex	*register_mutex(enum e_MutexId id, int variant)
{
	t_mutexs	*m;

	m = mutexs();
	m->mutexs = ft_realloc(
			m->mutexs,
			sizeof(t_mutex *) * (m->count + 1),
			sizeof(t_mutex *) * (m->count + 2));
	m->mutexs[m->count] = malloc(sizeof(t_mutex));
	m->mutexs[m->count]->id = id;
	m->mutexs[m->count]->variant = variant;
	pthread_mutex_init(&m->mutexs[m->count]->mutex, NULL);
	pthread_mutex_init(&m->mutexs[m->count]->lock, NULL);
	m->mutexs[m->count]->is_lock = 0;
	m->mutexs[++m->count] = NULL;
	return (m->mutexs[m->count - 1]);
}

t_mutex	*get_mutex(enum e_MutexId id, int variant)
{
	t_mutex		**m;
	int			i;

	m = mutexs()->mutexs;
	i = 0;
	while (m[i])
	{
		if (m[i]->id == id && m[i]->variant == variant)
			return (m[i]);
		i++;
	}
	return (NULL);
}

void	destroy_mutexs(void)
{
	t_mutex	**m;
	int		i;

	m = mutexs()->mutexs;
	i = 0;
	while (m[i])
	{
		pthread_mutex_destroy(&m[i]->mutex);
		pthread_mutex_destroy(&m[i]->lock);
		free(m[i]);
		i++;
	}
	free(m);
	free(mutexs());
}
