/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:26:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/18 15:18:20 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
TBD
*/

int	philo_nr = 0;

pthread_mutex_t mutex;

void	*routine(void *arg)
{
	(void)arg;

	pthread_mutex_lock(&mutex);
	philo_nr++;
	printf("Hello from philo %d.\n", philo_nr);
	pthread_mutex_unlock(&mutex);
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
	pthread_mutex_init(&mutex, NULL);

	while (i < 4)
	{
		if (pthread_create(&philo[i], NULL, &routine, NULL))
		{
			 perror("pthread_create");
			return (1);
		}
		i++;
	}

	i = 0;
	while (i < 4)
	{
		if (pthread_join(philo[i], NULL))
		{
			perror("pthread_join"); // Include perror for better error handling
			return (2);
		}
		pthread_mutex_lock(&mutex);
		printf("philo thread %d has finished\n", i + 1);
		pthread_mutex_unlock(&mutex);
		i++;
	}

	pthread_mutex_destroy(&mutex);

	return (EXIT_SUCCESS);
}
