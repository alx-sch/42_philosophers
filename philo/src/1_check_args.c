/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_check_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:27:51 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/20 19:47:20 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains functions for validating command-line arguments passed
to the philosopher simulation program.
If invalid arguments are found, the program prints an appropriate error message
and usage instructions.
*/

#include "philo.h"

// IN FILE:

int		check_args(int argc, char **argv);

/**
Used in check_args().

Converts a string to an integer and validates the input.

There is no overflow detection, so it's the user's responsibility to ensure
that only numbers up to `INT_MAX` are used.

 @param str 	The argument to be validated.

 @return		`0` if the argument is valid;
				`1` if the argument is not a number or if the number is < 0.
 */
static int	is_valid_arg(const char *str)
{
	if (contains_digit(str) || ft_atoi(str) < 0)
		return (1);
	return (0);
}

/**
Used in check_args().

Validates the number of command-line arguments passed to the program.

 @param argc 	The number of command-line arguments.

 @return 		`0` if count of passed arguments is valid (4 or 5);
 				`1` otherwise.
*/
static int	check_arg_count(int argc)
{
	if (argc < 5 || argc > 6)
	{
		print_err_msg(ERR_ARGS_NR, NULL);
		print_usage();
		return (1);
	}
	return (0);
}

/**
Used in check_args().

Checks if the number of philosophers is valid (>= 1).

 @param arg 	The first command-line argument (argv[1]).

 @return 		`0` if the nr of philos is valid;
 				`1` if the nr of philos is < 1;
				`2` if argv[1] contains no digits.
*/
static int	check_first_arg(char *arg)
{
	if (contains_digit(arg))
		return (2);
	if (ft_atoi(arg) < 1)
	{
		print_err_msg(ERR_ARGS_0_P, NULL);
		print_usage();
		return (1);
	}
	return (0);
}

/**
Validates the command-line arguments passed to the program.
If invalid, it prints an error message and usage instructions.

Checks if:
 - The number of passed arguments is either 4 or 5;
 - Arguments contain digits;
 - 'nr of philos' is at least 1;
 - Other args are >= 0.

 @param argc 	The number of command-line arguments.
 @param argv 	An array of command-line argument strings.

 @return 		`0` if all arguments are valid;
 				`1` if not.
*/
int	check_args(int argc, char **argv)
{
	int	i;

	if (check_arg_count(argc) || check_first_arg(argv[1]) == 1)
		return (1);
	i = 1;
	while (i <= (argc - 1))
	{
		if (is_valid_arg(argv[i]))
		{
			ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
			ft_putstr_fd(ERR_ARGS_VAL_1, STDERR_FILENO);
			ft_putstr_fd(ERR_ARGS_VAL_2, STDERR_FILENO);
			ft_putstr_fd(RESET, STDERR_FILENO);
			print_usage();
			return (1);
		}
		i++;
	}
	return (0);
}