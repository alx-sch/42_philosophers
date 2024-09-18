/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:26:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/18 18:07:35 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
TBD
*/

int	philo_nr = 0;

void	*routine(void *arg)
{
	t_data	*data_t;

	data_t = (t_data *)arg;
	pthread_mutex_lock(&data_t->mtx);
	philo_nr++;
	printf("Hello from philo %d.\n", philo_nr);
	pthread_mutex_unlock(&data_t->mtx);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t		philo[4];
	int				i;
	t_data			data;

	(void)argc;
	(void)argv;
	i = 0;

	init_data_struct(&data, argc, argv);

	while (i < 4)
	{
		if (pthread_create(&philo[i], NULL, &routine, &data))
		{
			print_err_msg(ERR_TR_CREATE, ERR_COLOR, 1);
			return (1);
		}
		i++;
	}

	i = 0;
	while (i < 4)
	{
		if (pthread_join(philo[i], NULL))
		{
			print_err_msg(ERR_TR_JOIN, ERR_COLOR, 1);
			return (2);
		}
		pthread_mutex_lock(&data.mtx);
		printf("philo thread %d has finished\n", i + 1);
		pthread_mutex_unlock(&data.mtx);
		i++;
	}

	pthread_mutex_destroy(&data.mtx);

	return (EXIT_SUCCESS);
}
