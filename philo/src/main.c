/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:26:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/05 16:49:29 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
TBD
*/

int	main(int argc, char **argv)
{
	//pthread_t		philo[ft_atoi(argv[1])];
	t_sim			sim;
	//t_ull			current_time;

	//i = 0;

	if (init_sim(&sim, argc, argv))
		return (1);

	if (start_sim(&sim))
		return (1);

	// current_time = get_time(&sim);
	// if (current_time == 0)
	// 	return (1);
	// else
	// 	sim.t_start_sim = current_time;

	// while (i < ft_atoi(argv[1]))
	// {
	// 	if (pthread_create(&philo[i], NULL, &routine, &sim.philos[i]))
	// 	{
	// 		print_err_and_clean(ERR_TR_CREATE, NULL);
	// 		return (1);
	// 	}
	// 	//printf("philo thread id: %lu\n", philo[i]);
	// 	i++;
	// }

	// i = 0;
	// while (i < ft_atoi(argv[1]))
	// {
	// 	if (pthread_join(&sim.philos[i], NULL))
	// 	{
	// 		print_err_and_clean(ERR_TR_JOIN, NULL);
	// 		return (1);
	// 	}
	// 	i++;
	// }

	cleanup_sim(&sim);

	return (0);
}
