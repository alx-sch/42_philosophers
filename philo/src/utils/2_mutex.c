/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:12:59 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/19 20:31:33 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// IN FILE:

int	mtx_act(t_mtx *mutex, t_mtx_act action);

/**
Performs an action on a mutex based on the specified action.

 @param 	mutex Pointer to a `pthread_mutex_t` mutex to operate on.
 @param 	action The action to perform on the mutex

 INIT: 		Initializes the mutex;
 LOCK: 		Locks the mutex;
 UNLOCK: 	Unlocks the mutex;
 DESTROY: 	Destroys the mutex.

 @return 	`0` on success;
			`1` on failure (if the corresponding pthread operation fails).
 */
int	mtx_act(t_mtx *mutex, t_mtx_act action)
{
	if (action == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			return (INIT);
	}
	else if (action == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			return (LOCK);
	}
	else if (action == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			return (UNLOCK);
	}
	else if (action == DESTROY)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			return (DESTROY);
	}
	return (0);
}
