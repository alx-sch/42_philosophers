/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:08:52 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/05 20:58:41 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Functions for cleaning up simulation resources. It includes routines to free
the memory allocated for philosophers and forks, as well as to destroy any
mutexes used for synchronization.
*/

#include "philo.h"

// IN FILE:

void	cleanup_sim(t_sim **sim_ptr);

/**
Used in `cleanup_sim()`.

Cleans up the fork resources for the simulation.

This function iterates through the forks associated with the simulation
and destroys each mutex lock. After that, it frees the memory allocated
for the fork array and sets the pointer to NULL to avoid dangling references.

 @param sim 	Pointer to the simulation structure containing fork resources.
*/
static void	clean_forks(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->nr_philo)
	{
		mtx_action(&sim->forks[i].fork, DESTROY);
		i++;
	}
	free(sim->forks);
	sim->forks = NULL;
}

/**
Used in `cleanup_sim()`.

Cleans up the philosopher resources for the simulation.

This function frees the memory allocated for the philosopher array and sets
the pointer to NULL to  prevent dangling references.

 @param sim 	Pointer to the sim structure containing philosopher resources.
*/
static void	clean_philos(t_sim *sim)
{
	free(sim->philos);
	sim->philos = NULL;
}

/**
Cleans up all resources associated with the simulation.

This function handles the cleanup of philosopher and fork resources,
as well as the print mutex, if initialized. It ensures that all allocated
memory is freed and sets the main simulation pointer to NULL to avoid
dangling references.

 @param sim_ptr 	Double pointer to the simulation structure, allowing for
					modification of the pointer itself to NULL after cleanup.
*/
void	cleanup_sim(t_sim **sim_ptr)
{
	t_sim	*sim;

	sim = *sim_ptr;
	if (!sim)
		return ;
	if (sim->forks)
		clean_forks(sim);
	if (sim->philos)
		clean_philos(sim);
	if (sim->mtx_print_init)
		mtx_action(&sim->mtx_print, DESTROY);
	free(sim);
	*sim_ptr = NULL;
}
