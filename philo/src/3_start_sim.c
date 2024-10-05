/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_start_sim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:39:52 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/05 16:48:57 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;

	print_action(philo, FORK, get_time(philo->sim) - philo->sim->t_start_sim);
	print_action(philo, EAT, get_time(philo->sim) - philo->sim->t_start_sim);
	precise_wait(philo->sim->t_eat, philo->sim);
	print_action(philo, SLEEP, get_time(philo->sim) - philo->sim->t_start_sim);
	precise_wait(philo->sim->t_sleep, philo->sim);
	print_action(philo, THINK, get_time(philo->sim) - philo->sim->t_start_sim);
	precise_wait(50, philo->sim);
	print_action(philo, DIE, get_time(philo->sim) - philo->sim->t_start_sim);
	if (FULL != 0)
		print_action(philo, STUFFED, get_time(philo->sim) - philo->sim->t_start_sim);
	return (NULL);
}

/**
Sets the starting time for the simulation by retrieving the current time.

 @param sim 	Pointer to the simulation structure to store the start time.

 @return 		`0` on success;
 				`1` if there was an error retrieving the time.
*/
static int	set_start_time(t_sim *sim)
{
	t_ull	time_start_sim;

	time_start_sim = get_time(sim);
	if (time_start_sim == 0)
		return (1);
	else
		sim->t_start_sim = time_start_sim;
	return (0);
}

int	start_sim(t_sim *sim)
{
	int		i;

	if (set_start_time(sim))
		return (1);
	i = 0;
	while (i < sim->nr_philo)
	{
		if (pthread_create(&sim->philos[i].thread_id, NULL, &routine, &sim->philos[i]))
		{
			print_err_and_clean(ERR_TR_CREATE, sim);  // Handle thread creation error
			return (1);
		}
		i++;
	}

	// Wait for all philosopher threads to finish
	i = 0;
	while (i < sim->nr_philo)
	{
		pthread_join(sim->philos[i].thread_id, NULL);
		i++;
	}
	return (0);
}


	// while (i < ft_atoi(argv[1]))
	// {
	// 	if (pthread_create(&philo[i], NULL, &routine, &sim))
	// 	{
	// 		print_err_and_clean(ERR_TR_CREATE, NULL);
	// 		return (1);
	// 	}
	// 	i++;
	// }
