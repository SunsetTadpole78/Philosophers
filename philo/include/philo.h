/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:44:40 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/18 09:10:16 by lroussel         ###   ########.fr       */
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
	struct s_simulation		*simulation;
}	t_philosopher;

typedef struct s_simulation
{
	int				count;
	int				time_to_die;
	int				time_to_eat;
	int				min_meals_count;
	int				time_to_sleep;
	long			start_time;
	int				stop;
	t_philosopher	*first;
}	t_simulation;

void			invalid_arguments(char **argv);
int				ft_strlen(char *str);
int				ft_atoi(char *str);
int				ft_is_uint(char *str);
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

t_simulation	*init_simulation(char **argv);
void			free_simulation(t_simulation *simulation);

int				is_correct(char **args);

int				take_forks(t_philosopher *thomas);
void			drop_forks(t_philosopher *thomas);

void			rip(t_philosopher *thomas);
long			get_last_eat(t_philosopher *thomas);
void			eat(t_philosopher *thomas);
void			go_sleep(t_philosopher *thomas);
void			think(t_philosopher *thomas);

int				is_dead(t_philosopher *thomas);
int				check_others(t_philosopher *thomas);

int				start_simulation(t_simulation *simulation);
int				is_stop(t_simulation *simulation);
int				check_others(t_philosopher *thomas);

void			check_meals(t_philosopher *thomas);

void			look_spaghetti_bowl(t_philosopher *thomas);
void			safe_display(char *message, t_philosopher *thomas,
					int exception);

long			timestramp(void);
long			simulation_timestramp(t_simulation *simulation);
void			ft_usleep(int ms);
long			get_start_time(t_simulation *simulation);

t_mutex			*register_mutex(enum e_MutexId id, int variant);
t_mutex			*get_mutex(enum e_MutexId id, int variant);
int				lock_mutex(enum e_MutexId id, int variant);
int				unlock_mutex(enum e_MutexId id, int variant);
void			unlock_all_mutexs(void);
void			destroy_mutexs(void);
#endif
