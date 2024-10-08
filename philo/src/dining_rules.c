/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 18:47:34 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/08 06:11:41 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
Checks whether the simulation should stop by accessing the `stop_sim` flag
in the simulation structure.

This function ensures thread safety by using a mutex to lock access to the
shared `stop_sim` variable.

 @param sim 	Pointer to the simulation struct containing the `stop_sim` flag.

 @return 		The value of the `stop_sim` flag:
				`1` if the simulation should stop;
				`0` otherwise.
*/
int	check_death(t_sim *sim)
{
	int	dead;

	mtx_action(&sim->mtx_philo_dead, LOCK);
	dead = sim->philo_dead;
	mtx_action(&sim->mtx_philo_dead, UNLOCK);
	return (dead);
}

/**
 *
 *
 *  odd / even: to prevent lock-order violations (more a helgrind issue, no deadlock arise during sim):
 * when multiple mutextes are lock by threads, the order must be consistent for all threads
 */
int	pick_forks(t_philo *philo)
{
	if (philo->odd)
	{
		if (mtx_action(&philo->left_fork->fork, LOCK))
			return (1);
		if (print_action(0, philo, FORK_L, 1))
			return (1);
		if (mtx_action(&philo->right_fork->fork, LOCK))
			return (1);
		if (print_action(0, philo, FORK_R, 1))
			return (1);
	}
	else
	{
		if (mtx_action(&philo->right_fork->fork, LOCK))
			return (1);
		if (print_action(0, philo, FORK_R, 1))
			return (1);
		if (mtx_action(&philo->left_fork->fork, LOCK))
			return (1);
		if (print_action(0, philo, FORK_L, 1))
			return (1);
	}
	return (0);
}

int	drop_forks(t_philo *philo)
{
	if (philo->odd)
	{
		if (mtx_action(&philo->right_fork->fork, UNLOCK))
			return (1);
		if (mtx_action(&philo->left_fork->fork, UNLOCK))
			return (1);
	}
	else
	{
		if (mtx_action(&philo->left_fork->fork, UNLOCK))
			return (1);
		if (mtx_action(&philo->right_fork->fork, UNLOCK))
			return (1);
	}
	return (1);
	return (0);
}

// int	pick_forks(t_philo *philo)
// {
// 	if (MORE == 0)
// 	{
// 		if (mtx_action(&philo->left_fork->fork, LOCK))
// 			return (1);
// 		print_action(0, philo, FORK, 1);
// 		if (mtx_action(&philo->right_fork->fork, LOCK))
// 			return (1);
// 		print_action(0, philo, FORK, 1);
// 	}
// 	else
// 	{
// 		if (mtx_action(&philo->left_fork->fork, LOCK))
// 			return (1);
// 		print_action(0, philo, FORK_L, 1);
// 		if (mtx_action(&philo->right_fork->fork, LOCK))
// 			return (1);
// 		print_action(0, philo, FORK_R, 1);
// 	}
// 	return (0);
// }

void	*dining(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		// FORK
		if (check_death(philo->sim))
			break ;
		if (philo->id % 2 == 1) // Odd philosophers
			pick_forks(philo);
		else
		{
			usleep(900);
			pick_forks(philo);
		}

		// EAT
		if (check_death(philo->sim))
			break ; // put down forks
		print_action(0, philo, EAT, 1);
		philo->meals_eaten++;
		precise_wait(philo->sim->t_eat);
		// Put down forks
		if (drop_forks(philo))
		{
			mtx_action(&philo->sim->mtx_philo_dead, LOCK);
			philo->sim->philo_dead = 1;
			mtx_action(&philo->sim->mtx_philo_dead, UNLOCK);
			printf(ERR_COLOR"ERROR\n"RESET);
			break;
		}

		// check if FULL
		if (philo->meals_eaten == philo->sim->max_meals)
		{
			mtx_action(&philo->sim->mtx_full_philos, LOCK);
			philo->sim->full_philos++;
			mtx_action(&philo->sim->mtx_full_philos, UNLOCK);
			if (FANCY != 0)
				print_action(0, philo, STUFFED, 1);
			break ;
		}

		// SLEEP
		if (check_death(philo->sim))
			break ;
		print_action(0, philo, SLEEP, 1);
		precise_wait(philo->sim->t_sleep);

		// THINK
		if (check_death(philo->sim))
			break ;
		print_action(0, philo, THINK, 1);
		//precise_wait(400); // thinking time

		//FULL
		// if (FULL != 0)
		// {
		// 	if (should_stop_sim(philo->sim))
		// 		break ;
		// 	print_action(get_time() - philo->sim->t_start_sim, philo, STUFFED, 1);
		// }

		// // DEATH CHECK
		// if (philo->id == 5) // DIES HERE!
		// {
		// 	record_time_of_death(philo);
		// 	mtx_action(&philo->sim->mtx_stop_sim, LOCK);
		// 	philo->sim->stop_sim = 1;
		// 	mtx_action(&philo->sim->mtx_stop_sim, UNLOCK);
		// 	usleep(200);
		// 	//precise_wait(1); // makes sure that 'die' message is print last
		// 	print_action(philo->timestamp_death, philo, DIE, 0);
		// }
	}
	return (NULL);
}

void	*monitoring(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	while (1)
	{
		mtx_action(&sim->mtx_full_philos, LOCK);
		if (sim->full_philos == sim->nr_philo)
		{
			mtx_action(&sim->mtx_full_philos, UNLOCK);
			break ;
		}
		mtx_action(&sim->mtx_full_philos, UNLOCK);
		mtx_action(&sim->mtx_philo_dead, LOCK);
		if (sim->philo_dead == 1)
		{
			mtx_action(&sim->mtx_philo_dead, UNLOCK);
			printf("%llu\tending simulation, someone died!\n", get_time() - sim->t_start_sim);
			break ;
		}
		mtx_action(&sim->mtx_philo_dead, UNLOCK);
		usleep(100); // reduces CPU load
	}
	return (NULL);
}
