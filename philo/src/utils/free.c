/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:08:52 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/18 18:11:50 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_err_msg(char *msg, char *color, int newline);

/**
Used in check_args().

Prints an error message to the standard error stream (stderr),
with additional formatting applied.

 @param msg 		The error message to be printed.
 @param color 		ANSI escape code formatting; no formatting if `NULL`.
 @param newline 	Flag to print the newline character after the error message
 					(`0` does not, otherwise does).
*/
void	print_err_msg(char *msg, char *color, int newline)
{
	if (color)
		ft_putstr_fd(color, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (newline)
		ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
}

// fct to exit with err msg and cleanup;