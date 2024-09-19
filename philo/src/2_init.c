/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:53:20 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/19 23:04:06 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// IN FILE:

int	init(t_data *data, int argc, char **argv);

static int	init_args(t_data *data, int argc, char **argv)
{
	if (check_args(argc, argv))
		return (1);
	data->nr_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	else
		data->max_meals = -1;
	return (0);
}

static int	init_data_struct(t_data *data, int argc, char **argv)
{
	if (init_args(data, argc, argv) || mtx_act(&data->mtx_pr, INIT))
		return (1);
	data->t_start = 0;
	data->end_simulation = 0;
	data->forks = NULL;
	data->philos = NULL;
	return (0);
}

// int init_forks(t_data *data)
// {
//     int i;

//     // Allocate memory for forks
//     data->forks = malloc(sizeof(t_fork) * data->nr_philo);
//     if (!data->forks)
//     {
//         print_err_msg(ERR_MALLOC, NULL);
//         return (1);
//     }

//     // Initialize each fork
//     for (i = 0; i < data->nr_philo; i++)
//     {
//         // Initialize mutex for each fork
//         if (mtx_act(&data->forks[i].fork, INIT))
//         {
//             print_err_msg(ERR_MUTEX_INIT, NULL);
//             return (1);
//         }
//         data->forks[i].fork_id = i; // Set fork ID
//     }

//     return (0);
// }


int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nr_philo);
	if (!data->philos)
	{
		print_err_msg(ERR_MALLOC, NULL);
		return (1);
	}


    for (i = 0; i < data->nr_philo; i++) {
        data->philos[i].data = data; // Point to the data structure
        data->philos[i].id = i; // Set philosopher ID
        data->philos[i].meals_eaten = 0; // Initialize meals eaten
        data->philos[i].done_eating = 0; // Initialize done eating flag
        data->philos[i].t_last_meal = 0; // Initialize last meal time
        data->philos[i].left_fork = &data->forks[i]; // Set left fork
        data->philos[i].right_fork = &data->forks[(i + 1) % data->nr_philo]; // Set right fork
        data->philos[i].thread_id = 0; // Initialize thread ID to an invalid value

        // Initialize other fields if necessary
    }
	return (0);
}

int	init(t_data *data, int argc, char **argv)
{
	if (init_data_struct(data, argc, argv) || init_philos(data))
		return (1);

	return (0);
}
