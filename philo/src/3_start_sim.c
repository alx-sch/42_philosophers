/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_start_sim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:39:52 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/05 12:55:00 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// void	*routine(void *arg)
// {
// 	t_sim	*sim;

// 	sim = (t_sim *)arg;
// 	print_philo_action(get_time() - sim->t_start_sim, pthread_self() / 100000, FORK, sim);
// 	print_philo_action(get_time() - sim->t_start_sim, pthread_self() / 100000, EAT, sim);
// 	precise_wait(sim->t_eat);
// 	print_philo_action(get_time() - sim->t_start_sim, pthread_self() / 100000, SLEEP, sim);
// 	precise_wait(sim->t_sleep);
// 	print_philo_action(get_time() - sim->t_start_sim, pthread_self() / 100000, THINK, sim);
// 	precise_wait(50);
// 	print_philo_action(get_time() - sim->t_start_sim, pthread_self() / 100000, DIE, sim);
// 	print_philo_action(get_time() - sim->t_start_sim, pthread_self() / 100000, FULL, sim);
// 	return (NULL);
// }

// int	start_sim(t_sim *sim)
// {
// 	t_ull	time_start_sim;
// 	int		i;

// 	time_start_sim = get_time();
// 	if (time_start_sim == 0)
// 		return (1);
// 	else
// 		sim->t_start_sim = time_start_sim;

// 	i = 0;
// 	while (i < sim->nr_philo)
// 	{
// 		// Create a thread for each philosopher
// 		if (pthread_create(&sim->philos[i].thread_id, NULL, &routine, &sim->philos[i]))
// 		{
// 			print_err_and_clean(ERR_TR_CREATE, sim);  // Handle thread creation error
// 			return (1);
// 		}
// 		i++;
// 	}

// 	// Wait for all philosopher threads to finish
// 	i = 0;
// 	while (i < sim->nr_philo)
// 	{
// 		pthread_join(sim->philos[i].thread_id, NULL);
// 		i++;
// 	}

// 	return (0);
// }


// 	while (i < ft_atoi(argv[1]))
// 	{
// 		if (pthread_create(&philo[i], NULL, &routine, &sim))
// 		{
// 			print_err_and_clean(ERR_TR_CREATE, NULL);
// 			return (1);
// 		}
// 		i++;
// 	}
