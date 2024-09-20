/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:44:46 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/20 20:49:01 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
TBD
*/

#include "philo.h"

// IN FILE:

long	get_time_in_ms(void);

/**
Get the current time in milliseconds.

 @return 	The current time in milliseconds as a long integer.
*/
long	get_time_in_ms(void)
{
	struct timeval	tv;
	long			time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}
