/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:26:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/05 13:55:10 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
TBD
*/

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;

	print_action(get_time() - philo->sim->t_start_sim, FORK, philo);
	print_action(get_time() - philo->sim->t_start_sim, EAT, philo);
	precise_wait(philo->sim->t_eat);
	print_action(get_time() - philo->sim->t_start_sim, SLEEP, philo);
	precise_wait(philo->sim->t_sleep);
	print_action(get_time() - philo->sim->t_start_sim, THINK, philo);
	precise_wait(50);
	print_action(get_time() - philo->sim->t_start_sim, DIE, philo);
	if (FULL != 0)
		print_action(get_time() - philo->sim->t_start_sim, STUFFED, philo);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t		philo[ft_atoi(argv[1])];
	int				i;
	t_sim			sim;

	i = 0;

	if (init_sim(&sim, argc, argv))
		return (1);

	while (i < ft_atoi(argv[1]))
	{
		if (pthread_create(&philo[i], NULL, &routine, &sim.philos[i]))
		{
			print_err_and_clean(ERR_TR_CREATE, NULL);
			return (1);
		}
		i++;
	}

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_join(philo[i], NULL))
		{
			print_err_and_clean(ERR_TR_JOIN, NULL);
			return (1);
		}
		i++;
	}

	cleanup_sim(&sim);

	return (0);
}
