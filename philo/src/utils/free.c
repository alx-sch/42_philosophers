/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:08:52 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/20 18:38:26 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_forks(t_sim *sim)
{
	int	i;

	if (sim->forks)
	{
		i = 0;
		while (i < sim->nr_philo)
		{
			mtx_act(&sim->forks[i].fork, DESTROY, NULL);
			i++;
		}
		free(sim->forks);
		sim->forks = NULL;
	}
}


void	free_data(t_sim *sim)
{
	free_forks(sim);
	if (sim->philos)
		free(sim->philos);
	mtx_act(&sim->mtx_pr, DESTROY, NULL);
}
