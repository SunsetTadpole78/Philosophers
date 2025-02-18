/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:18:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/18 09:18:25 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
