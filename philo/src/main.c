/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:26:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/20 20:15:43 by aschenk          ###   ########.fr       */
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

	if (init_simulation(&sim, argc, argv))
	{
		printf("init failed\n");
		return (1);
	}

	while (i < 4)
	{
		if (pthread_create(&philo[i], NULL, &routine, &sim))
		{
			print_err_msg(ERR_TR_CREATE, NULL);
			return (1);
		}
		i++;
	}

	i = 0;
	while (i < 4)
	{
		if (pthread_join(philo[i], NULL))
		{
			print_err_msg(ERR_TR_JOIN, NULL);
			return (1);
		}
		i++;
	}

	free_data(&sim);

	return (0);
}
