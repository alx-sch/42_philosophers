/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:27:51 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/19 22:27:47 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// IN FILE:

int		check_args(int argc, char **argv);

/**
Used in check_args().

Converts a string to an integer and validates the input.

This function converts the input string `str` to an integer using `ft_atoi`.

If the string represents a valid integer value > 0, the function returns the
converted integer value.

There is no overflow detection, so it's the user's responsibility to ensure
that only numbers up to `INT_MAX` are used

 @param str 	The input string to be validated and converted to an integer.

 @return		Returns the converted integer value if valid.
				Returns `-1` if the string does not represent a valid number
				or if the number is < 1.
 */
static int	is_valid_arg(const char *str)
{
	int	int_value;

	int_value = ft_atoi(str);
	if (int_value < 1)
		return (-1);
	return (int_value);
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

	if (!(argc == 5 || argc == 6))
	{
		print_err_msg(ERR_ARGS_NR, NULL);
		print_usage();
		return (1);
	}
	i = 1;
	while (i <= (argc - 1))
	{
		if (is_valid_arg(argv[i]) < 0)
		{
			print_err_msg(ERR_ARGS_VAL, NULL);
			print_usage();
			return (1);
		}
		i++;
	}
	return (0);
}
