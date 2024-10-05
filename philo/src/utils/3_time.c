/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:44:46 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/04 18:25:38 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
TBD
*/

#include "philo.h"

// IN FILE:

t_ull	get_time(void);
void	precise_wait(int duration_to_wait);

/**
Get the current time in milliseconds since the epoch (January 1, 1970).

 @return 	The current time in milliseconds as an unsigned 64-bit integer;
			`0` in case of an error.
 */
t_ull	get_time(void)
{
	struct timeval	tv;
	t_ull			time_in_ms;

	if (gettimeofday(&tv, NULL))
	{
		print_err_and_clean(ERR_GET_TIME, NULL); // might use it later in program, so that data ist to be cleaned
		return (0);
	}
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}

/**
Halts execution for a specified duration with improved precision.

While `usleep()` may not provide exact timing due to potential inaccuracies
in system scheduling etc., this custom function effectively mitigates these
limitations by relying on real-time checks at short intervals.

 @param 	duration_to_wait Duration in microseconds for which to wait.
*/
void	precise_wait(int duration_to_wait)
{
	t_ull	time_stop_waiting;

	time_stop_waiting = get_time() + duration_to_wait;
	while (get_time() < time_stop_waiting)
		usleep(duration_to_wait / 100);
}
