/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:19:12 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/19 23:02:49 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h> // thread fcts, like pthread_create()

typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

/**
TBD
*/
typedef enum e_mtx_act
{
	INIT = 1,
	LOCK,
	UNLOCK,
	DESTROY
}	t_mtx_act;


typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	t_data		*data;
	int			id;
	pthread_t	thread_id;
	long		meals_eaten;
	int			done_eating;
	long		t_last_meal;
	t_fork		*left_fork;
	t_fork		*right_fork;
}	t_philo;

typedef struct s_data
{
	int		nr_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		max_meals;
	long	t_start;
	int		end_simulation;
	t_fork	*forks;
	t_philo	*philos;
	t_mtx	mtx_pr;
}	t_data;

#endif
