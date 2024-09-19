/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:08:52 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/19 18:18:29 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_err_msg(char *msg, char *color, int nl, pthread_mutex_t *mtx);

/**
Used in check_args().

Prints an error message to the standard error stream (stderr),
with additional formatting applied.

 @param msg 		The error message to be printed.
 @param color 		ANSI escape code formatting; no formatting if `NULL`.
 @param nl 	Flag to print the newline character after the error message
 					(`0` does not, otherwise does).
*/
void	print_err_msg(char *msg, char *color, int nl, pthread_mutex_t *mtx_pr)
{
	if (mtx_pr != NULL)
		pthread_mutex_lock(mtx_pr);
	if (color)
		ft_putstr_fd(color, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (nl)
		ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	if (mtx_pr != NULL)
		pthread_mutex_unlock(mtx_pr);
}
