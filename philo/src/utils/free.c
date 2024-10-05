/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:08:52 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/05 18:14:20 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// IN FILE:

void	cleanup_sim(t_sim **sim_ptr);

static void	clean_forks(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->nr_philo)
	{
		mtx_act(&sim->forks[i].fork, DESTROY);
		i++;
	}
	free(sim->forks);
	sim->forks = NULL;
}

void	cleanup_sim(t_sim **sim_ptr)
{
	t_sim	*sim;

	sim = *sim_ptr;
	if (!sim)
	{
		printf("already cleaned up!\n");
		return ;
	}
	printf("cleaning up!\n");
	if (sim->forks)
		clean_forks(sim);
	if (sim->philos)
	{
		free(sim->philos);
		sim->philos = NULL;
	}
	mtx_act(&sim->mtx_print, DESTROY);
	free(sim);
	*sim_ptr = NULL;
}
