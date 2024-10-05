/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_sim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:53:20 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/05 18:14:00 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// IN FILE:

int	init_sim(t_sim **sim, int argc, char **argv);

static int	init_args(t_sim *sim, int argc, char **argv)
{
	if (check_args(argc, argv))
		return (1);
	sim->nr_philo = ft_atoi(argv[1]);
	sim->t_die = ft_atoi(argv[2]);
	sim->t_eat = ft_atoi(argv[3]);
	sim->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->max_meals = ft_atoi(argv[5]);
	else
		sim->max_meals = -1;
	return (0);
}

/**
NULL passed to mtx_act as there is no need to free anything yet (and avoid having
a not created mutex destroyed).
 */
static int	init_sim_state(t_sim *sim, int argc, char **argv)
{
	sim->end_simulation = 0;
	sim->forks = NULL;
	sim->philos = NULL;
	if (init_args(sim, argc, argv))
		return (1);
	if (mtx_act(&sim->mtx_print, INIT))
		return (1);
	return (0);
}

/*
clean up as and passed NULL as free_data fct inly handles fully or not at all
initialized fork mtx arrays
*/
int	init_forks(t_sim *sim)
{
	int	i;

	sim->forks = malloc(sizeof(t_fork) * sim->nr_philo);
	if (!sim->forks)
	{
		print_err_and_clean(ERR_MALLOC);
		return (1);
	}
	i = 0;
	while (i < sim->nr_philo)
	{
		if (i == 6)
		{
			while (--i >= 0)
				mtx_act(&sim->forks[i].fork, DESTROY);
			free(sim->forks);
			sim->forks = NULL;
			return (1);
		}

		if (mtx_act(&sim->forks[i].fork, INIT))
		{
			while (--i >= 0)
				mtx_act(&sim->forks[i].fork, DESTROY);
			free(sim->forks);
			sim->forks = NULL;
			return (1);
		}
		sim->forks[i].fork_id = i + 1;
		i++;
	}
	return (0);
}

int	init_philos(t_sim *sim)
{
	int	i;

	sim->philos = malloc(sizeof(t_philo) * sim->nr_philo);
	if (!sim->philos)
	{
		print_err_and_clean(ERR_MALLOC);
		return (1);
	}
	i = 0;
	while (i < sim->nr_philo)
	{
		sim->philos[i].sim = sim;
		sim->philos[i].id = i + 1;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].done_eating = 0;
		sim->philos[i].left_fork = &sim->forks[i];
		sim->philos[i].right_fork = &sim->forks[(i + 1) % sim->nr_philo];
		i++;
	}
	i = 0;
	return (0);
}

int	init_sim(t_sim **sim, int argc, char **argv)
{
	*sim = malloc(sizeof(t_sim));
	if (!(*sim))
	{
		print_err_and_clean(ERR_MALLOC);
		return (1);
	}
	if (init_sim_state(*sim, argc, argv) || init_forks(*sim) || init_philos(*sim))
		return (1);

	return (0);
}