/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:53:20 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/05 18:01:46 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
Checks if the given string represents the value zero.

This function checks whether the input string `str` is equal to "0", "+0",
or "-0". It returns 1 (true) if the string matches any of these, indicating
that the string represents a zero value. Otherwise, it returns 0 (false).

 @param str 	The input string to be checked.

 @return		`1` if the string is "0", "+0", or "-0", indicating the string
				represents zero.
				Returns `0` if the string does not represent zero.
 */
// static int	is_zero(const char *str)
// {
// 	int	is_zero;

// 	is_zero = !ft_strcmp(str, "0") || !ft_strcmp(str, "+0")
// 		|| !ft_strcmp(str, "-0");
// 	return (is_zero);
// }

// static int	is_valid_arg(const char *str)
// {
// 	int	int_value;

// 	int_value = ft_atoi(str);
// 	if (int_value == 0 && !is_zero(str))
// 		return (-1);
// 	return (int_value);
// }

/**
Prints an error message to the standard error stream (stderr),
with additional formatting applied.

 @param msg 			The error message to be printed. This should be a
						descriptive string about the error that occurred.
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

static void	print_usage(void)
{
	print_err_msg("Usage: './philo nr_philo t_die t_eat t_sleep (nr_meals)'\n",
		YELLOW, 1);
	print_err_msg("")
	ft_putstr_fd(RESET, STDERR_FILENO);
}

void	init_data_struct(t_data *data, int argc, char **argv)
{
	if (!(argc >= 2 && argc <=6))
	{
		print_err_msg(ERR_ARGS_NR, ERR_COLOR, 1);
		print_usage();
		exit(EXIT_FAILURE);
	}
	data->argc = argc;
	data->argv = argv;
}
