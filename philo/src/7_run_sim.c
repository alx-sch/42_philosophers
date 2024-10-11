/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_run_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:39:52 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/11 20:58:14 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Implements functions for running the simulation by creating and joining
monitor and philosopher threads.
*/

#include "philo.h"

// IN FILE:

int	run_sim(t_sim *sim);

/**
Starts the monitor thread to observe the state of the simulation.

A short delay (`usleep`) is introduced to ensure the monitor is fully
initialized before the philosopher threads begin their dining routines.

 @param	sim 	Pointer to the sim structure, which holds the philosopher data.

 @return		`0` on success;
				`1` if there was an error creating the monitor thread.
*/
static int	start_monitoring(t_sim *sim)
{
	if (sim->max_meals == 0)
		return(0);
	if (pthread_create(&sim->monitor, NULL, &monitor, sim))
	{
		print_err_msg(ERR_TR_CREATE);
		return (1);
	}
	usleep(100);
	return (0);
}

/**
Joins the monitor thread, waiting for it to finish execution.

 @param	sim 	Pointer to the sim structure, which holds the philosopher data.

 @return		`0` on success;
				`1` if there was an error joining the monitor thread.
*/
static int	end_monitoring(t_sim *sim)
{
	if (sim->max_meals == 0)
		return(0);
	if (pthread_join(sim->monitor, NULL))
	{
		print_err_msg(ERR_TR_JOIN);
		return (1);
	}
	return (0);
}

/**
Starts the dining simulation by creating threads for each philosopher. Each
thread will run the `dining` function that simulates the philosopher's behavior.

 @param	sim 	Pointer to the sim structure, which holds the philosopher data.

 @return		`0` on success;
				`1` if there was an error creating any of the threads.
*/
static int	start_dining(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->nr_philo)
	{
		if (pthread_create(&sim->philos[i].thread_id, NULL, &eat_sleep_think,
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
Ends the dining simulation by joining all philosopher threads, waiting until
all philosophers have completed their execution.

 @param	sim 	Pointer to the sim structure, which holds the philosopher data.

 @return		`0` on success;
				`1` if there was an error joining any of the threads.
*/
static int	end_dining(t_sim *sim)
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
to set the start time, create threads for the monitor and each philosopher,
and join those threads after the simulation has finished.

 @param	sim 	Pointer to the sim structure, which holds the philosopher data.

 @return		`0` on success;
				`1` if any of the steps fails (setting start time,
				thread creation, or thread joining).
*/
int	run_sim(t_sim *sim)
{
	if (set_start_time(sim))
		return (1);
	if (start_monitoring(sim))
		return (1);
	if (start_dining(sim))
		return (1);
	if (end_dining(sim))
		return (1);
	if (end_monitoring(sim))
		return (1);
	return (0);
}
