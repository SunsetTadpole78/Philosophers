/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:27:19 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/17 00:16:48 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct	s_philosopher
{
	int		id;
	long		last_eat;
	int		meals_count;
	int		dead;
	int		stop;
	int		started;
	pthread_t	life;
	pthread_t	check_death;
	struct s_philosopher	*next;
	struct s_simulation	*simulation;
}	t_philosopher;

typedef struct	s_simulation
{
	int	count;
	int	time_to_die;
	int	time_to_eat;
	int	min_meals_count;
	int	time_to_sleep;
	long	start_time;
	t_philosopher	*first;
	sem_t	*last_eat_sem;
	sem_t	*stop_sem;
	sem_t	*check_stop_sem;
	sem_t	*print_sem;
	sem_t	*forks_sem;
	sem_t	*deadlock_sem;
	sem_t	*started_sem;
}	t_simulation;

//checker
int	is_correct(char **args);

//errors
void	invalid_arguments(char **argv);

//initializer
t_simulation	*init_simulation(char **argv);

//simulation
void	start_simulation(t_simulation *simulation);


int	is_stop(t_philosopher *thomas);




//destructor
void	free_simulation(t_simulation *simulation);
void	unlink_semaphores(void);

//life
int	think(t_philosopher *thomas);
int	eat(t_philosopher *thomas);
int	take_forks(t_philosopher *thomas);
void	drop_forks(t_philosopher *thomas);
int	go_sleep(t_philosopher *thomas);

//libft
int	ft_is_uint(char *str);
int	ft_atoi(char *str);
int	ft_strlen(char *str);

//time
long	timestamp(void);
long	simulation_timestamp(t_simulation *simulation);
void	ft_usleep(int ms);

//display
int	safe_display(char *message, t_philosopher *thomas, int exception);

#endif
