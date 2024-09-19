/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:26:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/19 19:34:01 by aschenk          ###   ########.fr       */
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
	mtx_act(&data_t->mtx_a, LOCK);
	philo_nr++;
	printf("Hello from philo %d.\n", philo_nr);
	mtx_act(&data_t->mtx_a, UNLOCK);
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

	if (init_data_struct(&data, argc, argv))
		return (1);

	while (i < 4)
	{
		if (pthread_create(&philo[i], NULL, &routine, &data))
		{
			print_err_msg(ERR_TR_CREATE, ERR_COLOR, 1, &data.mtx_pr);
			return (1);
		}

		i++;
	}

	i = 0;
	while (i < 4)
	{
		if (pthread_join(philo[i], NULL))
		{
			print_err_msg(ERR_TR_JOIN, ERR_COLOR, 1, &data.mtx_pr);
			return (1);
		}
		if (mtx_act(&data.mtx_a, LOCK) || mtx_act(&data.mtx_pr, LOCK))
			return (1);
		printf("philo thread %d has finished\n", i + 1);
		i++;
		if (mtx_act(&data.mtx_pr, UNLOCK) || mtx_act(&data.mtx_a, UNLOCK))
			return (1);
	}

	mtx_act(&data.mtx_a, DESTROY);
	mtx_act(&data.mtx_pr, DESTROY);

	return (0);
}
