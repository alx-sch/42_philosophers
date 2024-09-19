/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:05:49 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/19 22:19:26 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// IN FILE:

void	print_usage(void);
void	print_err_msg(char *msg, t_data *data);

/**
Used in print_usage().

Prints a message to the standard error stream with formatting applied.

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
Handles and reports an unexpected error. This function prints an error message
to the standard error stream and performs cleanup on the provided data structure
if it is not `NULL`.

 @param msg 	Error message to be printed in error color and
 				suffixed with a newline.
 @param data 	A pointer to the data structure that needs to be cleaned up.
*/
void	print_err_msg(char *msg, t_data *data)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	if (data)
	{
		// free data
	}
}

/**
Used in check_args().

Prints the correct usage information for the program, including details about
each argument expected. It provides formatted error messages and explains the
purpose of each command-line argument.

Each message is printed with optional ANSI escape code formatting for emphasis
and clarity, using the `print_err_msg()` function to handle the details.
*/
void	print_usage(void)
{
	print_msg("Usage: './philo nr_philo t_die t_eat t_sleep [nr_meals]'\n",
		YELLOW, 1);
	print_msg("- nr_philo (number_of_philosophers): ", BOLD, 0);
	print_msg("The number of philosophers and also the number of forks.",
		NULL, 1);
	print_msg("- t_die (time_to_die) [in ms]: ", BOLD, 0);
	print_msg("If a philosopher did not start eating in 't_die' since the \
beginning of their last meal or the beginning of the simulation, they die.",
		NULL, 1);
	print_msg("- t_eat (time_to_eat) [in ms]: ", BOLD, 0);
	print_msg("The time it takes for a philosopher to eat. During that \
time, they will need to hold two forks.",
		NULL, 1);
	print_msg("- t_sleep (time_to_sleep) [in ms]: ", BOLD, 0);
	print_msg("The time a philosopher will spend sleeping.", NULL, 1);
	print_msg("- nr_meals (number_of_times_each_philosopher_must_eat) \
(optional argument): ", BOLD, 0);
	print_msg("If all philosophers have eaten at least 'nr_meals' times, \
the simulation stops. If not specified, the simulation stops when a \
philosopher dies.", NULL, 1);
}
