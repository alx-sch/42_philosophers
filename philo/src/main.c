/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:26:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/05 17:44:31 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
TBD
*/

void	*routine(void *arg)
{
	(void)arg;
	printf("Test from threads\n");
	sleep(1);
	printf("ENDING THREAD\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	// pthread_t	t1;
	// pthread_t	t2;
	t_data		data;

	(void)argc;
	(void)argv;

	init_data_struct(&data, argc, argv);

	// if (pthread_create(&t1, NULL, &routine, NULL))
	// 	return (1);

	// if (pthread_create(&t2, NULL, &routine, NULL))
	// 	return (2);

	// if (pthread_join(t1, NULL))
	// 	return (3);

	// if (pthread_join(t2, NULL))
	// 	return (4);

	return (EXIT_SUCCESS);
}
