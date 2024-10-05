/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:19:12 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/04 14:24:15 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h> // thread fcts, like pthread_create()

typedef pthread_mutex_t		t_mtx; // abbreviate 'pthread_mutex_t' to 't_mtx'
typedef unsigned long long	t_ull;
typedef struct s_sim		t_sim;

/**
Represents the actions that can be performed on a mutex:
 - INIT
 - LOCK
 - UNLOCK
 - DESTROY
*/
typedef enum e_mtx_act
{
	INIT = 1,
	LOCK,
	UNLOCK,
	DESTROY
}	t_mtx_act;

typedef enum e_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
	FULL
}	t_action;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	t_sim		*sim;
	int			id;
	pthread_t	thread_id;
	int			meals_eaten;
	int			done_eating;
	t_ull		t_last_meal;
	t_fork		*left_fork;
	t_fork		*right_fork;
}	t_philo;

typedef struct s_sim
{
	int			nr_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			max_meals;
	int			end_simulation;
	t_ull		t_start_sim;
	t_fork		*forks;
	t_philo		*philos;
	t_mtx		mtx_print;
}	t_sim;

#endif
