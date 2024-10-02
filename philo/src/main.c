/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:26:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/27 08:20:37 by aschenk          ###   ########.fr       */
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
	mtx_act(&sim->mtx_print, LOCK, sim);
	printf("Hello from philo %lu.\n", pthread_self());
	mtx_act(&sim->mtx_print, UNLOCK, sim);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t		philo[4];
	int				i;
	t_sim			sim;

	i = 0;

	if (init_sim(&sim, argc, argv))
		return (1);

	while (i < 4)
	{
		if (pthread_create(&philo[i], NULL, &routine, &sim))
		{
			print_err_and_clean(ERR_TR_CREATE, NULL);
			return (1);
		}
		i++;
	}

	i = 0;
	while (i < 4)
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
