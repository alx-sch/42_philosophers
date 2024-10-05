/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:19:12 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/05 21:47:21 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This header file defines custom types and data structures.
*/

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h> // Thread functions, like pthread_create() etc.

typedef pthread_mutex_t		t_mtx; // Abbreviation for 'pthread_mutex_t'
typedef unsigned long long	t_ull; // Abbreviation for 'unsigned long long'
typedef struct s_sim		t_sim;

/**
Enumeration for representing various actions that can be performed on a mutex:
 - INIT:	Initializes the mutex.
 - LOCK:	Locks the mutex to ensure exclusive access.
 - UNLOCK:	Unlocks the mutex, allowing access to other threads.
 - DESTROY:	Destroys the mutex and releases associated resources.
*/
typedef enum e_mtx_action
{
	INIT = 1,
	LOCK,
	UNLOCK,
	DESTROY
}	t_mtx_action;

/**
Enumeration for representing the various actions a philosopher can take:
 - FORK:	Indicates that a philosopher is picking up a fork.
 - EAT:		Philosopher starts eating.
 - SLEEP:	Philosopher starts sleeping.
 - THINK:	Philosopher starts thinking.
 - DIE:		Indicates that the philosopher has died.
 - STUFFED:	Indicates that a philosopher has eaten enough and is no
			longer participating.
*/
typedef enum e_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
	STUFFED
}	t_action;

/**
Structure representing a fork in the dining philosophers problem:
 - fork_id:	An identifier for the fork.
 - fork:	A mutex associated with the fork to control access.
*/
typedef struct s_fork
{
	int		fork_id;
	t_mtx	fork;
}	t_fork;

/**
Structure representing a philosopher in the dining philosophers problem:
 - sim:				A pointer to the simulation structure, allowing access
					to shared data.
 - id:				The philosopher's identifier.
 - thread_id:		The identifier for the philosopher's thread.
 - meals_eaten:		Counter for the number of meals the philosopher has eaten.
 - done_eating:		Indicates whether the philosopher has finished eating.
 - is_alive:		A flag indicating whether the philosopher is still alive.
 - t_last_meal:		Timestamp of the philosopher's last meal in milliseconds.
 - left_fork:		A pointer to the philosopher's left fork.
 - right_fork:		A pointer to the philosopher's right fork.
*/
typedef struct s_philo
{
	t_sim		*sim;
	int			id;
	pthread_t	thread_id;
	int			meals_eaten;
	int			done_eating;
	int			is_alive;
	t_ull		t_last_meal;
	t_fork		*left_fork;
	t_fork		*right_fork;
}	t_philo;

/**
Structure representing the overall simulation state:
 - nr_philo:	Total number of philosophers participating in the simulation.
 - t_die:		Time in milliseconds after which a philosopher dies if they
				haven't start eating.
 - t_eat:		Time in ms a philosopher takes to eat.
 - t_sleep:		Time in milliseconds a philosopher sleeps after eating.
 - max_meals:	Max. number of meals a philosopher can eat before they stop
 				dining; -1 means unlimited.
 - end_sim:		Flag indicating whether the simulation should end.
 - t_start_sim:	Timestamp for when the simulation started.
 - forks:		Array of forks available for the philosophers.
 - philos:		Array of philosophers participating in the simulation.
 - mtx_print:	Mutex used for synchronizing output to the console (printing).
 - mtx_print_init:	Flag indicating whether the print mutex has been initialized.
*/
typedef struct s_sim
{
	int			nr_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			max_meals;
	int			end_sim;
	t_ull		t_start_sim;
	t_fork		*forks;
	t_philo		*philos;
	t_mtx		mtx_print;
	int			mtx_print_init;
}	t_sim;

#endif
