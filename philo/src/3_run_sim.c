/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_run_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:39:52 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/06 06:15:54 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Implements functions for starting and ending the simulation by
creating and joining philosopher threads, respectively.
*/

#include "philo.h"

// IN FILE:

int	run_sim(t_sim *sim);

/**
Used in `run_sim()`.

Sets the starting time for the simulation by retrieving the current time right
before the philosopher threads are created.

 @param sim 	Pointer to the simulation structure to store the start time.

 @return 		`0` on success;
 				`1` if there was an error retrieving the time.
*/
static int	set_start_time(t_sim *sim)
{
	t_ull	time_start_sim;

	time_start_sim = get_time();
	if (time_start_sim == 0)
		return (1);
	else
		sim->t_start_sim = time_start_sim;
	return (0);
}

/**
Used in `run_sim()`.

Starts the simulation by creating threads for each philosopher. Each thread
will run the `dining` function that simulates the philosopher's behavior.

 @param	sim 	Pointer to the sim structure, which holds the philosopher data.

 @return		`0` on success;
				`1` if there was an error creating any of the threads.
*/
static int	start_sim(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->nr_philo)
	{
		if (pthread_create(&sim->philos[i].thread_id, NULL, &dining,
				&sim->philos[i]))
		{
			print_err_msg(ERR_TR_CREATE);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
Used in `run_sim()`.

Ends the simulation by joining all philosopher threads.

This function waits for all philosopher threads to finish by calling
`pthread_join()` on each one. This ensures that the main thread waits until all
philosopher threads have completed their execution.

 @param	sim 	Pointer to the sim structure, which holds the philosopher data.

 @return		`0` on success;
				`1` if there was an error joining any of the threads.
*/
static int	end_sim(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->nr_philo)
	{
		if (pthread_join(sim->philos[i].thread_id, NULL))
		{
			print_err_msg(ERR_TR_JOIN);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
Runs the entire simulation.

This function orchestrates the simulation by calling the necessary functions
to set the start time, create threads for each philosopher, and join those
threads after the simulation has finished.

 @param	sim 	Pointer to the sim structure, which holds the philosopher data.

 @return		`0` on success;
				`1` if any of the steps fails (setting start time,
				thread creation, or thread joining).
*/
int	run_sim(t_sim *sim)
{
	if (set_start_time(sim))
		return (1);
	if (start_sim(sim))
		return (1);
	if (end_sim(sim))
		return (1);
	return (0);
}
