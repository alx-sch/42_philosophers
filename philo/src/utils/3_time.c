/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:44:46 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/27 08:09:55 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
TBD
*/

#include "philo.h"

// IN FILE:

uint64_t	get_time(void);

/**
Get the current time in milliseconds since the epoch (January 1, 1970).

 @return 	The current time in milliseconds as an unsigned 64-bit integer;
			`0` in case of an error.
 */
uint64_t	get_time(void)
{
	struct timeval	tv;
	uint64_t		time_in_ms;

	if (gettimeofday(&tv, NULL))
	{
		print_err_and_clean(ERR_GET_TIME, NULL); // might use it later in program, so that data ist to be cleaned
		return (0);
	}
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
	return (0);
}
