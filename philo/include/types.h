/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:19:12 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/19 18:23:48 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h> // thread fcts, like pthread_create()

/**
TBD
*/
typedef enum e_mutex_action
{
	INIT = 1,
	LOCK,
	UNLOCK,
	DESTROY
}	t_mutex_action;

typedef struct s_data
{
	int				nr_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nr_meals;
	int				nr_meals_set;
	pthread_mutex_t	mtx_pr;
	pthread_mutex_t	mtx_a;
}	t_data;

#endif
