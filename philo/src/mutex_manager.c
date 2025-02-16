/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:33:26 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/16 11:03:42 by lroussel         ###   ########.fr       */
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
	pthread_mutex_init(&(m->mutexs[m->count]->mutex), NULL);
	pthread_mutex_init(&(m->mutexs[m->count]->lock), NULL);
	m->mutexs[m->count]->is_lock = 0;
	m->mutexs[++m->count] = NULL;
	return (m->mutexs[m->count - 1]);
}

t_mutex	*get_mutex_by_id(enum e_MutexId id, int variant)
{
	t_mutexs	*mu;
	t_mutex		**m;
	int			i;

	mu = mutexs();
	m = mu->mutexs;
	i = 0;
	while (m[i])
	{
		if (m[i]->id == id && m[i]->variant == variant)
			return (m[i]);
		i++;
	}
	return (NULL);
}

int	is_lock(t_mutex *mutex)
{
	int	v;

	pthread_mutex_lock(&mutex->lock);
	v = mutex->is_lock;
	pthread_mutex_unlock(&mutex->lock);
	return (v);
}

int	lock_mutex(enum e_MutexId id, int variant)
{
	t_mutex	*mutex;

	mutex = get_mutex_by_id(id, variant);
	pthread_mutex_lock(&mutex->lock);
	mutex->is_lock = 1;
	pthread_mutex_unlock(&mutex->lock);
	return (pthread_mutex_lock(&mutex->mutex));
}

int	unlock_mutex(enum e_MutexId id, int variant)
{
	t_mutex	*mutex;

	mutex = get_mutex_by_id(id, variant);
	pthread_mutex_lock(&mutex->lock);
	mutex->is_lock = 0;
	pthread_mutex_unlock(&mutex->lock);
	return (pthread_mutex_unlock(&mutex->mutex));
}

void	unlock_all_mutexs(void)
{
	t_mutex	**m;
	int		i;

	m = mutexs()->mutexs;
	i = 0;
	while (m[i])
	{
		if (is_lock(m[i]))
			unlock_mutex(m[i]->id, m[i]->variant);
		i++;
	}
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
