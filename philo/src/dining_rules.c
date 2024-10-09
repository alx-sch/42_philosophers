/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 18:47:34 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/09 14:05:29 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
Checks whether the simulation should stop by accessing the `philo_dead` flag.

 @param sim 	Pointer to the simulation struct containing the `philo_dead` flag.

 @return		The value of the `stop_sim` flag:
				`1` if the simulation should stop;
				`0` otherwise.
*/
int	check_death(t_philo *philo)
{
	int		dead;
	int		this_philo_died;

	this_philo_died = 0;
	mtx_action(&philo->sim->mtx_philo_dead, LOCK);
	dead = philo->sim->philo_dead;
	if (!dead)
	{
		if (get_time() - philo->t_last_meal > (t_ull)philo->sim->t_die)
		{
			philo->sim->philo_dead = 1;
			dead = 1;
			this_philo_died = 1;
			record_time_of_death(philo);
		}
	}
	mtx_action(&philo->sim->mtx_philo_dead, UNLOCK);
	if (this_philo_died)
	{
		usleep(200);
		print_action(philo->timestamp_death, philo, DIE, 0);
	}
	return (dead);
}


// // DEATH CHECK
// 		if (philo->id == 5) // DIES HERE!
// 		{
// 			record_time_of_death(philo);
// 			mtx_action(&philo->sim->mtx_stop_sim, LOCK);
// 			philo->sim->stop_sim = 1;
// 			mtx_action(&philo->sim->mtx_stop_sim, UNLOCK);
// 			usleep(200);
// 			//precise_wait(1); // makes sure that 'die' message is print last
// 			print_action(philo->timestamp_death, philo, DIE, 0);
// 		}

/**
Attempts to pick up the left and right forks for the philosopher.

If a fork cannot be picked up, the philosopher will spin in a loop,
continuously attempting to acquire the forks. This behavior ensures that the
philosopher can pick up the forks as soon as they are available.

The order of locking is differentiated based on whether the philosopher
is odd or even to prevent lock-order violations (while not necessarily resulting
in deadlocks here, Helgrind / `-fsanitize=thread` checks for this).

 @param philo 	A pointer to the philosopher attempting to pick up the forks.

 @return		`0` on success;
				`1` if there is an error locking a mutex or printing the action.
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

/**
Releases the left and right forks held by the philosopher.

The order of unlocking is differentiated based on whether the philosopher
is odd or even to prevent lock-order violations (while not necessarily resulting
in deadlocks here, Helgrind / `-fsanitize=thread` checks for this).

 @param philo 	A pointer to the philosopher structure releasing the forks.

 @return		`0` on success;
				`1` if there is an error unlocking a mutex.
*/
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
	return (0);
}

int	perform_fork_action(t_philo *philo)
{
	if (philo->odd)
		return (pick_forks(philo));
	else
	{
		usleep(900);
		return (pick_forks(philo));
	}
}

int	perform_eat_action(t_philo *philo)
{
	philo->meals_eaten++;
	philo->t_last_meal = get_time();
	if (print_action(0, philo, EAT, 1))
		return (1);
	precise_wait(philo->sim->t_eat);
	if (drop_forks(philo))
		return (1);
	return (0);
}

/**
return (1);  // Early return on failure
return (2); // Successfully full and done thinking
return (0);  // Not full yet
 */
int	check_full(t_philo *philo)
{
	if (philo->meals_eaten == philo->sim->max_meals)
	{
		if (FANCY != 0)
			if (print_action(0, philo, STUFFED, 1))
				return (1);
		if (print_action(0, philo, THINK, 1))
			return (1);
		return (2);
	}
	return (0);
}

void	*dining(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_death(philo))
			break ;
		(void)perform_fork_action(philo);
		if (check_death(philo))
		{
			drop_forks(philo);
			break ;
		}
		(void)perform_eat_action(philo);
		if (check_full(philo) == 2)
			break ;

		// SLEEP
		if (check_death(philo))
			break ;
		print_action(0, philo, SLEEP, 1);
		precise_wait(philo->sim->t_sleep);

		// THINK
		if (check_death(philo))
			break ;
		print_action(0, philo, THINK, 1);
		precise_wait(philo->sim->t_think * ALTRUISM_FACTOR);
	}
	return (NULL);
}
