/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_print_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:49:37 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/07 21:13:57 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains functions responsible for printing the actions of
philosophers in the dining simulation. The output includes a timestamp,
the philosopher's ID, and a description of the action being performed.

When the `EMOJI` and/or `FULL` (all meals eaten) flags are set during
compilation (e.g., `make EMOJI=1 FULL=1`), additional information and
visual cues are printed to enhance the output.
*/

#include "philo.h"

// IN FILE:

int	print_action(t_ull timestamp, t_philo *philo, t_action action,
		int recalc_timestamp);

/**
Prints the action of a philosopher WITHOUT emojis.

 @param timestamp 	The timestamp of the action in milliseconds.
 @param action 		The action being performed, represented as an enum type.
 @param philo 		A pointer to the philosopher structure performing the action.
*/
static void	print_standard(t_ull timestamp, t_philo *philo, t_action action)
{
	if (action == DIE)
		(void)printf(ERR_COLOR);
	(void)printf("%llu\t%d\t", timestamp / ROUND * ROUND, philo->id);
	if (action == FORK)
		(void)printf("has taken a fork\n");
	else if (action == EAT)
		(void)printf("is eating\n");
	else if (action == SLEEP)
		(void)printf("is sleeping\n");
	else if (action == THINK)
		(void)printf("is thinking\n");
	else if (action == DIE)
		(void)printf("died\n");
	else if (action == STUFFED)
		(void)printf("is full\n");
	if (action == DIE)
		(void)printf(RESET);
}

/**
Prints the action of a philosopher WITH emojis.

 @param timestamp 	The timestamp of the action in milliseconds.
 @param action 		The action being performed, represented as an enum type.
 @param philo 		A pointer to the philosopher structure performing the action.
*/
static void	print_more(t_ull timestamp, t_philo *philo, t_action action)
{
	if (action == DIE)
		(void)printf(ERR_COLOR);
	else if (action == STUFFED)
		(void)printf(YELLOW);
	(void)printf("%llu\t%d\t", timestamp / ROUND * ROUND, philo->id);
	if (action == FORK_L)
		(void)printf("🥄←\thas taken their fork\t(%d) left\n", philo->left_fork->fork_id);
	if (action == FORK_R)
		(void)printf("→🥄\thas taken their fork\t(%d) right\n", philo->right_fork->fork_id);
	else if (action == EAT)
		(void)printf("🍝\tis eating\t\t(%d. meal)\n", philo->meals_eaten + 1);
	else if (action == SLEEP)
		(void)printf("💤\tis sleeping\n");
	else if (action == THINK)
		(void)printf("💡\tis thinking\n");
	else if (action == DIE)
		(void)printf("💀\tdied\n");
	else if (action == STUFFED)
		(void)printf("🫃\tis full\t\t\t(%d meals)\n", philo->meals_eaten);
	if (action == DIE || action == STUFFED)
		(void)printf(RESET);
}

/**
Prints the action of a philosopher with a timestamp, ensuring thread-safe access
to the standard output using a mutex.

The `recalc_timestamp` flag helps prevent timestamp mix-ups in multithreaded
execution by recalculating the timestamp just before printing.

Depending on the `EMOJI` and `FULL` flags (defined during compilation), the
function will print additional visual cues and information (default: no emojis
or additional info).

The timestamp is rounded to the nearest `ROUND` milliseconds (also defined during
compilation) before being printed to enhance readability (default: no rounding).

 @param timestamp 	The timestamp of the action in milliseconds.
 @param action 		The action being performed, represented as an enum type:
					- FORK: Takes a fork;
					- EAT: Starts eating;
					- SLEEP: Starts sleeping;
					- THINK: Starts thinking;
					- DIE: Dies;
					- STUFFED: Has eaten all their meals.
 @param philo 		A pointer to the philosopher structure performing the action.
 @param recalc_timestamp 	`0`: Use the provided timestamp as is;
							`1`: Recalculate the timestamp just before printing.

 @return 			`0` if the action was printed successfully;
 					`1` if there was an error in locking or unlocking the mutex.
*/
int	print_action(t_ull timestamp, t_philo *philo, t_action action,
		int recalc_timestamp)
{
	if (mtx_action(&philo->sim->mtx_print, LOCK))
		return (1);
	if (recalc_timestamp)
		timestamp = get_time() - philo->sim->t_start_sim;
	if (FANCY == 0)
		print_standard(timestamp, philo, action);
	else
		print_more(timestamp, philo, action);
	if (mtx_action(&philo->sim->mtx_print, UNLOCK))
		return (1);
	return (0);
}
