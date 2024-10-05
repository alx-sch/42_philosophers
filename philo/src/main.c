/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:26:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/04 19:01:37 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
TBD
*/

void	*routine(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	print_philo_action(get_time() - sim->t_start_sim, pthread_self() / 100000, FORK, sim);
	print_philo_action(get_time() - sim->t_start_sim, pthread_self() / 100000, EAT, sim);
	precise_wait(sim->t_eat);
	print_philo_action(get_time() - sim->t_start_sim, pthread_self() / 100000, SLEEP, sim);
	precise_wait(sim->t_sleep);
	print_philo_action(get_time() - sim->t_start_sim, pthread_self() / 100000, THINK, sim);
	precise_wait(50);
	print_philo_action(get_time() - sim->t_start_sim, pthread_self() / 100000, DIE, sim);
	print_philo_action(get_time() - sim->t_start_sim, pthread_self() / 100000, FULL, sim);
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
		if (pthread_create(&philo[i], NULL, &routine, &sim))
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
