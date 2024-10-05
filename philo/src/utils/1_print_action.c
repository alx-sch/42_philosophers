/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_print_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:49:37 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/05 14:48:45 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains functions responsible for printing the actions of
philosophers in the dining philosopher simulation. The output includes a
timestamp, the philosopher's ID, and a description of the action being
performed.

When the emoji and/or 'full state' (all meals eaten) settings are enabled
during compilation (e.g., `make EMOJI=1 FULL=1`), additional information and
visual cues are printed to enhance the output.

The printing functions are designed to be thread-safe, using a mutex to prevent
race conditions during concurrent output.
*/

#include "philo.h"

// IN FILE:

int	print_action(t_philo *philo, t_action action, t_ull timestamp);

/**
Prints the action of a philosopher WITHOUT emojis. This function locks the
printing mutex before output and unlocks it afterward to ensure thread-safe
output.

Special color formatting is applied for the 'DIE' and 'STUFFED' actions.

 @param timestamp 	The timestamp of the action in milliseconds.
 @param action 		The action being performed, represented as an enum type:
					- FORK: Takes a fork;
					- EAT: Starts eating;
					- SLEEP: Starts sleeping;
					- THINK: Starts thinking;
					- DIE: Dies;
					- STUFFED: Has eaten all their meals.
 @param philo 		A pointer to the philosopher structure performing the action.

 @return 			`0` if the action was printed successfully;
 					`1` if there was an error in locking or unlocking the mutex.
*/
static int	print_without_emojis(t_philo *philo, t_action action,
	t_ull timestamp)
{
	if (mtx_act(&philo->sim->mtx_print, LOCK, philo->sim))
		return (1);
	if (action == DIE)
		(void)printf(ERR_COLOR);
	else if (action == STUFFED)
		(void)printf(YELLOW);
	(void)printf("%llu\t%d\t", timestamp, philo->id);
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
	if (action == DIE || action == STUFFED)
		(void)printf(RESET);
	if (mtx_act(&philo->sim->mtx_print, UNLOCK, philo->sim))
		return (1);
	return (0);
}

/**
Prints the action of a philosopher WITH emojis. This function locks the
printing mutex before output and unlocks it afterward to ensure thread-safe
output.

Special color formatting is applied for the 'DIE' and 'STUFFED' actions.

 @param timestamp 	The timestamp of the action in milliseconds.
 @param action 		The action being performed, represented as an enum type:
					- FORK: Takes a fork;
					- EAT: Starts eating;
					- SLEEP: Starts sleeping;
					- THINK: Starts thinking;
					- DIE: Dies;
					- STUFFED: Has eaten all their meals.
 @param philo 		A pointer to the philosopher structure performing the action.

 @return 			`0` if the action was printed successfully;
 					`1` if there was an error in locking or unlocking the mutex.
*/
static int	print_with_emojis(t_philo *philo, t_action action, t_ull timestamp)
{
	if (mtx_act(&philo->sim->mtx_print, LOCK, philo->sim))
		return (1);
	if (action == DIE)
		(void)printf(ERR_COLOR);
	else if (action == STUFFED)
		(void)printf(YELLOW);
	(void)printf("%llu\t%d\t", timestamp, philo->id);
	if (action == FORK)
		(void)printf("🥄\thas taken a fork\n");
	else if (action == EAT)
		(void)printf("🍝\tis eating\n");
	else if (action == SLEEP)
		(void)printf("💤\tis sleeping\n");
	else if (action == THINK)
		(void)printf("💡\tis thinking\n");
	else if (action == DIE)
		(void)printf("💀\tdied\n");
	else if (action == STUFFED)
		(void)printf("🫃\tis full\n");
	if (action == DIE || action == STUFFED)
		(void)printf(RESET);
	if (mtx_act(&philo->sim->mtx_print, UNLOCK, philo->sim))
		return (1);
	return (0);
}

/**
Prints the action of a philosopher with a timestamp, ensuring thread-safe access
to the standard output using a mutex.

Depending on the global configuration (`EMOJI` flag), the function will either
print the actions with emojis or without them (default: without emojis).

 @param timestamp 	The timestamp of the action in milliseconds.
 @param action 		The action being performed, represented as an enum type:
					- FORK: Takes a fork;
					- EAT: Starts eating;
					- SLEEP: Starts sleeping;
					- THINK: Starts thinking;
					- DIE: Dies;
					- STUFFED: Has eaten all their meals.
 @param philo 		A pointer to the philosopher structure performing the action.

 @return 			`0` if the action was printed successfully;
 					`1` if there was an error in locking or unlocking the mutex.
*/
int	print_action(t_philo *philo, t_action action, t_ull timestamp)
{
	if (EMOJI == 0)
		return (print_without_emojis(philo, action, timestamp));
	else
		return (print_with_emojis(philo, action, timestamp));
}
