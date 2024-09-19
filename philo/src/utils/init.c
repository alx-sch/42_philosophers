/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:53:20 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/19 19:39:08 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_args(t_data *data, int argc, char **argv)
{
	if (check_args(argc, argv))
		return (1);
	data->nr_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->nr_meals_set = 1;
		data->nr_meals = ft_atoi(argv[5]);
	}
	else
	{
		data->nr_meals_set = 0;
		data->nr_meals = -1;
	}
	return (0);
}

int	init_data_struct(t_data *data, int argc, char **argv)
{
	if (init_args(data, argc, argv) || mtx_act(&data->mtx_pr, INIT)
		|| mtx_act(&data->mtx_a, INIT))
		return (1);
	return (0);
}
