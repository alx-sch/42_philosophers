/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:26:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/19 22:55:41 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
TBD
*/

void	*routine(void *arg)
{
	t_data	*data_t;

	data_t = (t_data *)arg;
	mtx_act(&data_t->mtx_pr, LOCK);
	printf("Hello from philo %lu.\n", pthread_self());
	mtx_act(&data_t->mtx_pr, UNLOCK);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t		philo[4];
	int				i;
	t_data			data;

	i = 0;

	if (init(&data, argc, argv))
		return (1);

	while (i < 4)
	{
		if (pthread_create(&philo[i], NULL, &routine, &data))
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

	mtx_act(&data.mtx_pr, DESTROY);

	return (0);
}
