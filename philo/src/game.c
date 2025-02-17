/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:15:30 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/17 08:45:46 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestramp(void)
{
	struct timeval	t;
	long			time;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000 + t.tv_usec / 1000);
	return (time);
}

long	game_timestramp(t_game *game)
{
	return (timestramp() - game->start_time);
}

void	ft_usleep(int ms)
{
	long	finish;
	long	actual;

	actual = timestramp();
	finish = actual + ms;
	while (actual < finish)
	{
		actual = timestramp();
		usleep(1);
	}
}

void	safe_display(char *message, t_philosopher *thomas, int exception)
{
	lock_mutex(PRINT_F, 0);
	if (exception || !is_stop(thomas->game))
		printf("%li %i %s\n", game_timestramp(thomas->game), thomas->id, message);
	unlock_mutex(PRINT_F, 0);
}

long	get_start_time(t_game *game)
{
	long	v;

	lock_mutex(START_TIME, 0);
	v = game->start_time;
	unlock_mutex(START_TIME, 0);
	return (v);
}

int	get_time_to_die(t_game *game)
{
	int	v;

	lock_mutex(TIME_TO_DIE, 0);
	v = game->time_to_die;
	unlock_mutex(TIME_TO_DIE, 0);
	return (v);
}

int	get_time_to_eat(t_game *game)
{
	int	v;

	lock_mutex(TIME_TO_EAT, 0);
	v = game->time_to_eat;
	unlock_mutex(TIME_TO_EAT, 0);
	return (v);
}

void	rip(t_philosopher *thomas)
{
	if (is_stop(thomas->game))
		return ;
	lock_mutex(STOP, 0);
	thomas->game->stop = 1;
	unlock_mutex(STOP, 0);
	safe_display("died", thomas, 1);
}

int	is_stop(t_game *game)
{
	int	v;

	lock_mutex(STOP, 0);
	v = game->stop;
	unlock_mutex(STOP, 0);
	return (v);
}

int	is_dead(t_philosopher *thomas)
{
	long	time;

	if (is_stop(thomas->game))
		return (1);
	time = get_last_eat(thomas);
	if (time == -1)
		time = get_start_time(thomas->game);
	else
		time -= get_time_to_eat(thomas->game);
	if (timestramp() - time > get_time_to_die(thomas->game))
	{
		rip(thomas);
		return (1);
	}
	return (0);
}

int	check_others(t_philosopher *thomas)
{
	t_philosopher	*other_thomas;

	other_thomas = thomas->next;
	while (other_thomas->id != thomas->id)
	{
		if (is_dead(other_thomas))
			return (1);
		other_thomas = other_thomas->next;
	}
	return (0);
}

void	think(t_philosopher *thomas)
{
	if (is_dead(thomas))
		return ;
	safe_display("is thinking", thomas, 0);
}

int	thomas_count(t_game *game)
{
	int	v;

	lock_mutex(COUNT, 0);
	v = game->count;
	unlock_mutex(COUNT, 0);
	return (v);
}

void	look_spaghetti_bowl(t_philosopher *thomas)
{
	while (!is_dead(thomas))
		usleep(1);
}

int	take_fork(t_philosopher *thomas, int id, int other_id)
{
	lock_mutex(FORK, id);
	if (is_dead(thomas))
	{
		unlock_mutex(FORK, id);
		if (other_id != -1)
			unlock_mutex(FORK, other_id);
		return (0);
	}
	safe_display("has taken a fork", thomas, 0);
	return (1);
}

int	take_forks(t_philosopher *thomas)
{
	if (is_dead(thomas))
		return (0);
	if (thomas_count(thomas->game) == 1)
	{
		look_spaghetti_bowl(thomas);
		return (0);
	}
	if (thomas->id % 2 == 0)
	{
		if (!take_fork(thomas, thomas->next->id, -1))
			return (0);
		if (!take_fork(thomas, thomas->id, thomas->next->id))
			return (0);
	}
	else
	{
		if (!take_fork(thomas, thomas->id, -1))
			return (0);
		if (!take_fork(thomas, thomas->next->id, thomas->id))
			return (0);
	}
	return (1);
}

long	get_last_eat(t_philosopher *thomas)
{
	long	v;

	lock_mutex(LAST_EAT, thomas->id);
	v = thomas->last_eat;
	unlock_mutex(LAST_EAT, thomas->id);
	return (v);
}

void	set_last_eat(t_philosopher *thomas)
{
	lock_mutex(LAST_EAT, thomas->id);
	thomas->last_eat = timestramp() + (thomas->game->time_to_eat);
	unlock_mutex(LAST_EAT, thomas->id);
}

void	eat(t_philosopher *thomas)
{
	if (is_dead(thomas))
		return ;
	set_last_eat(thomas);
	safe_display("is eating", thomas, 0);
	while (timestramp() < get_last_eat(thomas))
	{
		if (check_others(thomas))
			return ;
		usleep(1);
	}
}

void	drop_forks(t_philosopher *thomas)
{
	unlock_mutex(FORK, thomas->id);
	unlock_mutex(FORK, thomas->next->id);
}

long	get_last_sleep(t_philosopher *thomas)
{
	long	v;

	lock_mutex(LAST_SLEEP, thomas->id);
	v = thomas->last_sleep;
	unlock_mutex(LAST_SLEEP, thomas->id);
	return (v);
}

void	set_last_sleep(t_philosopher *thomas)
{
	lock_mutex(LAST_SLEEP, thomas->id);
	thomas->last_sleep = timestramp() + (thomas->game->time_to_sleep);
	unlock_mutex(LAST_SLEEP, thomas->id);
}

void	go_sleep(t_philosopher *thomas)
{
	if (is_dead(thomas))
		return ;
	set_last_sleep(thomas);
	safe_display("is sleeping", thomas, 0);
	while (timestramp() < get_last_sleep(thomas))
	{
		if (is_dead(thomas))
			return ;
		if (check_others(thomas))
			return ;
		usleep(1);
	}
}

void	*life(void *args)
{
	t_philosopher	*thomas;
	int				unlock_forks;

	thomas = (t_philosopher *)args;
	lock_mutex(START_TIME, 0);
	if (thomas->game->start_time == -1)
		thomas->game->start_time = timestramp();
	unlock_mutex(START_TIME, 0);
	while (!is_dead(thomas))
	{
		think(thomas);
		unlock_forks = take_forks(thomas);
		eat(thomas);
		if (unlock_forks)
			drop_forks(thomas);
		go_sleep(thomas);
	}
	return (args);
}

int	start_game(t_game *game)
{
	t_philosopher	*cur;

	cur = game->first;
	while (cur)
	{
		pthread_create(&cur->thread, NULL, life, cur);
		cur = cur->next;
		if (cur->id == 1)
			break ;
	}
	return (1);
}
