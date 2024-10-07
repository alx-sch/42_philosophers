/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_sim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:53:20 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/07 17:04:03 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains functions for setting up the simulation state and for
creating the fork and philosopher structures.
These functions ensure that all required resources are allocated and properly
configured before the simulation begins.
*/

#include "philo.h"

// IN FILE:

int	init_sim(t_sim **sim, int argc, char **argv);

/**
Initializes the simulation parameters from command line arguments.
This function checks the validity of the arguments, converts them to integers,
and assigns them to the corresponding fields in the simulation structure.

 @param sim 	Pointer to the simulation structure to initialize.
 @param argc 	The argument count from the command line.
 @param argv 	The argument vector from the command line.

 @return 		`0` on success;
				`1` if any of the arguments are invalid.
*/
static int	init_args(t_sim *sim, int argc, char **argv)
{
	if (check_args(argc, argv))
		return (1);
	sim->nr_philo = ft_atoi(argv[1]);
	sim->t_die = ft_atoi(argv[2]);
	sim->t_eat = ft_atoi(argv[3]);
	sim->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->max_meals = ft_atoi(argv[5]);
	else
		sim->max_meals = -1;
	return (0);
}

/**
Sets initial values for the simulation state and initializes a mutex used for
printing and checking for a simulation stop.

 @param sim 	Pointer to the simulation structure to initialize.

 @return 		`0` on success;
				`1` if argument initialization or mutex initialization fails.
*/
static int	init_sim_state(t_sim *sim, int argc, char **argv)
{
	sim->stop_sim = 0;
	sim->forks = NULL;
	sim->philos = NULL;
	sim->mtx_print_init = 0;
	sim->mtx_stop_sim_init = 0;
	if (init_args(sim, argc, argv))
		return (1);
	if (mtx_action(&sim->mtx_print, INIT))
		return (1);
	sim->mtx_print_init = 1;
	if (mtx_action(&sim->mtx_stop_sim, INIT))
		return (1);
	sim->mtx_stop_sim_init = 1;
	return (0);
}

/**
This function allocates memory for the forks used by philosophers in the
simulation, and initializes their mutexes.

 @param sim 	Pointer to the simulation structure containing fork data.

 @return 		`0` on success;
				`1` if memory allocation or mutex initialization fails.
*/
static int	init_forks(t_sim *sim)
{
	int	i;

	sim->forks = malloc(sizeof(t_fork) * sim->nr_philo);
	if (!sim->forks)
	{
		print_err_msg(ERR_MALLOC);
		return (1);
	}
	i = 0;
	while (i < sim->nr_philo)
	{
		if (mtx_action(&sim->forks[i].fork, INIT))
		{
			while (i > 0)
				mtx_action(&sim->forks[--i].fork, DESTROY);
			free(sim->forks);
			sim->forks = NULL;
			return (1);
		}
		sim->forks[i].fork_id = i + 1; // actually needed?
		i++;
	}
	return (0);
}

/**
Initializes the philosophers participating in the simulation by allocating
memory for their structs and setting their initial state, including the
assignment of forks.

 @param sim 	Pointer to the simulation structure containing philosopher data.

 @return 		`0` on success;
				`1` if memory allocation fails.
*/
static int	init_philos(t_sim *sim)
{
	int	i;

	sim->philos = malloc(sizeof(t_philo) * sim->nr_philo);
	if (!sim->philos)
	{
		print_err_msg(ERR_MALLOC);
		return (1);
	}
	i = 0;
	while (i < sim->nr_philo)
	{
		sim->philos[i].sim = sim;
		sim->philos[i].id = i + 1;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].done_eating = 0;
		sim->philos[i].is_alive = 1;
		sim->philos[i].left_fork = &sim->forks[i];
		sim->philos[i].right_fork = &sim->forks[(i + 1) % sim->nr_philo];
		i++;
	}
	return (0);
}

/**
Initializes the simulation by allocating memory for the simulation structure
and setting up the initial state, forks, and philosophers.

 @param sim 	Double pointer to the simulation structure to be initialized.
 @param argc 	The argument count from the command line.
 @param argv 	The argument vector from the command line.

 @return 		`0` on success;
				`1` if memory allocation or initialization fails.
*/
int	init_sim(t_sim **sim, int argc, char **argv)
{
	*sim = malloc(sizeof(t_sim));
	if (!(*sim))
	{
		print_err_msg(ERR_MALLOC);
		return (1);
	}
	if (init_sim_state(*sim, argc, argv))
		return (1);
	if (init_forks(*sim))
		return (1);
	if (init_philos(*sim))
		return (1);
	return (0);
}
