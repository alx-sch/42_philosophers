/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:27:51 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/10 17:46:03 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
Used in is_valid_arg().

Checks if the given string represents the value zero.

This function checks whether the input string `str` is equal to "0", "+0",
or "-0". It returns 1 (true) if the string matches any of these, indicating
that the string represents a zero value. Otherwise, it returns 0 (false).

 @param str 	The input string to be checked.

 @return		`1` if the string is "0", "+0", or "-0", indicating the string
				represents zero.
				Returns `0` if the string does not represent zero.
 */
static int	is_zero(const char *str)
{
	int	is_zero;

	is_zero = !ft_strcmp(str, "0") || !ft_strcmp(str, "+0")
		|| !ft_strcmp(str, "-0");
	return (is_zero);
}

/**
Used in check_args().

Converts a string to an integer and validates the input.

This function converts the input string `str` to an integer using `ft_atoi`.
If the converted value is zero, it checks if the string actually represents
zero using the `is_zero` function (as ft_atoi also returns 0 when invalid input
is passed).

If the string represents a valid integer value >= 0, the function returns the
converted integer value.

 @param str 	The input string to be validated and converted to an integer.

 @return		Returns the converted integer value if valid.
				Returns `-1` if the string does not represent a valid number
				or if the number is < 0.
 */
static int	is_valid_arg(const char *str)
{
	int	int_value;

	int_value = ft_atoi(str);
	if ((int_value == 0 && !is_zero(str)) || int_value < 0)
		return (-1);
	return (int_value);
}

/**
Used in check_args().

Prints an error message to the standard error stream (stderr),
with additional formatting applied.

 @param msg 		The error message to be printed.
 @param color 		ANSI escape code formatting; no formatting if `NULL`.
 @param newline 	Flag to print the newline character after the error message
 					(`0` does not, otherwise does).
*/
static void	print_err_msg(char *msg, char *color, int newline)
{
	if (color)
		ft_putstr_fd(color, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (newline)
		ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
}

/**
Used in check_args().

*/
static void	print_usage(void)
{
	print_err_msg("Usage: './philo nr_philo t_die t_eat t_sleep (nr_meals)'\n",
		YELLOW, 1);
	print_err_msg("- nr_philo (number_of_philosophers): ", BOLD, 0);
	print_err_msg("The number of philosophers and also the number of forks.",
		NULL, 1);
	print_err_msg("- t_die (time_to_die) [in ms]: ", BOLD, 0);
	print_err_msg("If a philosopher did not start eating in 't_die' since the \
beginning of their last meal or the beginning of the simulation, they die.",
		NULL, 1);
	print_err_msg("- t_eat (time_to_eat) [in ms]: ", BOLD, 0);
	print_err_msg("The time it takes for a philosopher to eat. During that \
time, they will need to hold two forks.",
		NULL, 1);
	print_err_msg("- t_sleep (time_to_sleep) [in ms]: ", BOLD, 0);
	print_err_msg("The time a philosopher will spend sleeping.", NULL, 1);
	print_err_msg("- nr_meals (number_of_times_each_philosopher_must_eat) \
(optional argument): ", BOLD, 0);
	print_err_msg("If all philosophers have eaten at least 'nr_meals' times, \
the simulation stops. If not specified, the simulation stops when a \
philosopher dies.", NULL, 1);
}
/**
 0 fails

*/

int	check_args(int argc, char **argv)
{
	int	i;

	if (!(argc == 5 || argc == 6))
	{
		print_err_msg(ERR_ARGS_NR, ERR_COLOR, 1);
		print_usage();
		return (0);
	}
	i = 1;
	while (i <= (argc - 1))
	{
		if (is_valid_arg(argv[i]) < 0)
		{
			print_err_msg(ERR_ARGS_VAL, ERR_COLOR, 1);
			print_usage();
			return (0);
		}
		i++;
	}
	return (1);
}
