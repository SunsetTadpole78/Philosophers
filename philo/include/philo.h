/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:44:40 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/13 18:21:06 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct	s_fork
{
	int	philosopher_id;
	int	is_used;
}	t_fork;

typedef struct	s_philosopher
{
	int		id;
	int		alive;
	int		is_eating;
	int		is_thinking;
	int		is_sleeping;
	t_fork	*left_fork;
	t_fork	*right_fork;
	struct s_philosopher	*next;
}	t_philosopher;

typedef struct	s_game
{
	int	count;
	t_philosopher	*first;
	t_fork		**forks;
}	t_game;

int	ft_strlen(char *str);
int	ft_atoi(char *str);
int	ft_is_uint(char *str);

t_game	*init_game(char **argv);
void	free_game(t_game *game);

int	is_correct(char **args);

# endif
