/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:44:40 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/17 17:27:05 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

enum	e_MutexId
{
	FORK,
	START_TIME,
	PRINT_F,
	LAST_EAT,
	LAST_SLEEP,
	MEALS_COUNT,
	TIME_TO_DIE,
	TIME_TO_EAT,
	STOP,
	COUNT
};

typedef struct s_mutex
{
	enum e_MutexId	id;
	int				variant;
	pthread_mutex_t	mutex;
	int				is_lock;
	pthread_mutex_t	lock;
}	t_mutex;

typedef struct s_mutexs
{
	t_mutex			**mutexs;
	int				count;
}	t_mutexs;

typedef struct s_philosopher
{
	int						id;
	long					last_eat;
	long					last_sleep;
	int						meals_count;
	pthread_t				thread;
	t_mutex					*left_fork;
	t_mutex					*right_fork;
	struct s_philosopher	*next;
	struct s_game			*game;
}	t_philosopher;

typedef struct s_game
{
	int				count;
	int				time_to_die;
	int				time_to_eat;
	int				min_meals_count;
	int				time_to_sleep;
	long			start_time;
	int				stop;
	t_philosopher	*first;
}	t_game;

int		ft_strlen(char *str);
int		ft_atoi(char *str);
int		ft_is_uint(char *str);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

t_game	*init_game(char **argv);
void	free_game(t_game *game);

int		is_correct(char **args);

int		start_game(t_game *game);
int		is_dead(t_philosopher *thomas);
long	get_last_eat(t_philosopher *thomas);
int		is_stop(t_game *game);

t_mutex	*register_mutex(enum e_MutexId id, int variant);
t_mutex	*get_mutex_by_id(enum e_MutexId id, int variant);
int		lock_mutex(enum e_MutexId id, int variant);
int		unlock_mutex(enum e_MutexId id, int variant);
void	unlock_all_mutexs(void);
void	destroy_mutexs(void);
#endif
