/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:44:46 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/05 19:07:20 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file provides utility functions for time management in the dining
philosophers simulation. It includes functions to retrieve the current
time and to implement a precise waiting mechanism.
*/

#include "philo.h"

// IN FILE:

t_ull	get_time(void);
int		precise_wait(int duration_to_wait);

/**
Get the current time in milliseconds since the epoch (January 1, 1970).

 @param sim 	Pointer to a data struct to be freed in case of error.

 @return 		The current time in milliseconds;
				`0` in case of an error (or if it's 00:00:00 on 1/1/1970...)
 */
t_ull	get_time(void)
{
	struct timeval	tv;
	t_ull			time_in_ms;

	if (gettimeofday(&tv, NULL))
	{
		print_err_msg(ERR_GET_TIME);
		return (0);
	}
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}

/**
Halts execution for a specified duration with improved precision.

This function utilizes a combination of `get_time()` and short sleeps
to provide a more accurate waiting period. While traditional sleep functions
like `usleep()` may suffer from inaccuracies due to system scheduling, this
implementation checks the current time at regular intervals, effectively
mitigating such limitations.

The `SLEEP_INTERVALS` constant is defined in `philo.h`.

 @param	duration_to_wait 	Duration in milliseconds for which to wait.
 @param	sim 				Pointer to a data struct to be freed
 							in case of error.

 @return					`0` if the wait was successful;
							`1` if there was an error retrieving the time.
*/
int	precise_wait(int duration_to_wait)
{
	t_ull	time_stop_waiting;
	t_ull	current_time;

	time_stop_waiting = get_time();
	if (time_stop_waiting == 0)
		return (1);
	time_stop_waiting += duration_to_wait;
	while (1)
	{
		current_time = get_time();
		if (current_time == 0)
			return (1);
		if (current_time >= time_stop_waiting)
			break ;
		usleep(duration_to_wait / SLEEP_INTERVALS);
	}
	return (0);
}
