/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_check_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:27:51 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/20 19:43:01 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// IN FILE:

int		check_args(int argc, char **argv);

/**
Used in is_valid_arg().

Checks if the given string represents the value zero.

This function checks whether the input string `str` is equal to "0", "+0",
or "-0". It returns 1 (true) if the string matches any of these, indicating
that the string represents a zero value. Otherwise, it returns 0 (false).

 @param str 	The input string to be checked.

 @return		`0` if the string is "0", "+0", or "-0", indicating the string
				represents zero;
				`1` if the string does not represent zero.
 */
static int	is_zero(const char *str)
{
	if (!ft_strcmp(str, "0") || !ft_strcmp(str, "+0") || !ft_strcmp(str, "-0"))
		return (0);
	else
		return (1);
}

/**
Used in check_args().

Converts a string to an integer and validates the input.

This function converts the input string `str` to an integer using `ft_atoi`.

If the string represents a valid integer value >= 0, the function returns the
converted integer value.

There is no overflow detection, so it's the user's responsibility to ensure
that only numbers up to `INT_MAX` are used

 @param str 	The input string to be validated and converted to an integer.

 @return		`0` if the argument is valid;
				`1` if the string does not represent a number
				or if the number is < 1.
 */
static int	is_valid_arg(const char *str)
{
	int	int_value;

	int_value = ft_atoi(str);
	if ((int_value == 0 && is_zero(str)) || int_value < 0)
		return (1);
	return (0);
}

/**
Used in check_args().

Validates the number of command-line arguments passed to the program.

 @param argc 	The number of command-line arguments.

 @return 		`0` if the argument count is valid (4 or 5 passed arguments);
 				`1` otherwise.
*/
static int	check_arg_count(int argc)
{
	if (argc != 5 && argc != 6)
	{
		print_err_msg(ERR_ARGS_NR, NULL);
		print_usage();
		return (1);
	}
	return (0);
}

/**
Used in check_args().

Checks if the passed number of philosophers is valid (>= 1).

 @param arg 	The first command-line argument (argv[1]).

 @return 		`0` if the nr of philos is valid,
 				`1` if the nr of philos is invalid.
*/
static int	check_first_arg(char *arg)
{
	if (is_zero(arg) == 0 || ft_atoi(arg) < 0)
	{
		print_err_msg(ERR_ARGS_0_P, NULL);
		print_usage();
		return (1);
	}
	return (0);
}

/**
Validates the command-line arguments passed to the program.

Checks if the number of passed arguments is valid (either 4 or 5). If the
number of arguments is incorrect, it prints an error message and usage
instructions.

For each argument provided, it validates whether the argument is acceptable
by calling `is_valid_arg()`. If an invalid argument is found (not int > 0),
it prints an error message and usage instructions.

 @param argc 		The number of command-line arguments.
 @param argv 		An array of command-line argument strings.

 @return 			Returns `0` if all arguments are valid,
 					`1` if there is an error in the argument count or
					if any argument is invalid.
*/
int	check_args(int argc, char **argv)
{
	int	i;

	if (check_arg_count(argc) || check_first_arg(argv[1]))
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
