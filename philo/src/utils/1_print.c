/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:05:49 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/20 19:37:43 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Utility functions for printing messages to the terminal with optional
formatting and handling error reporting.
*/

#include "philo.h"

// IN FILE:

void	print_usage(void);
void	print_err_msg(char *msg, t_sim *sim);

/**
Used in print_usage().

Prints a message to the standard error stream with optional formatting applied.

 @param msg 		The error message to be printed.
 @param color 		ANSI escape code formatting; no formatting if `NULL`.
 @param nl 			Flag to print the newline character after the error message
 					(`0` does not, otherwise does).
*/
static void	print_msg(char *msg, char *color, int nl)
{
	if (color)
		ft_putstr_fd(color, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (nl)
		ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
}

/**
Used in check_args().

Prints the correct usage information for the program
*/
void	print_usage(void)
{
	print_msg("Usage: './philo nr_philo t_die t_eat t_sleep [nr_meals]'\n",
		YELLOW, 1);
	print_msg("- nr_philo: ", BOLD, 0);
	print_msg("The number of philosophers and also the number of forks.",
		NULL, 1);
	print_msg("- t_die [ms]: ", BOLD, 0);
	print_msg("If a philosopher did not start eating in 't_die' since the \
beginning of their last meal, they die.",
		NULL, 1);
	print_msg("- t_eat [ms]: ", BOLD, 0);
	print_msg("The time it takes for a philosopher to eat. During that \
time, they will need to hold two forks.",
		NULL, 1);
	print_msg("- t_sleep [ms]: ", BOLD, 0);
	print_msg("The time a philosopher will spend sleeping.", NULL, 1);
	print_msg("- nr_meals \
(optional argument): ", BOLD, 0);
	print_msg("If all philosophers have eaten at least 'nr_meals' times, \
the simulation stops.", NULL, 1);
}

/**
Prints a formatted error message to the standard error stream and
performs cleanup on the provided data structure, if provided.

 @param msg 	Error message to be printed.
 @param sim 	A pointer to the data structure that is to be cleaned up.
*/
void	print_err_msg(char *msg, t_sim *sim)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	if (sim)
		free_data(sim);
}
