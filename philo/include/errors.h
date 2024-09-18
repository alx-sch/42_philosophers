/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:54:08 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/18 16:14:40 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This header file defines error messages.
*/

#ifndef ERRORS_H
# define ERRORS_H

# define BOLD 			"\033[1m"
# define ERR_COLOR		"\033[91m\033[1m" // yed and bold
# define YELLOW			"\033[33m\033[1m" // yellow and bold
# define RESET			"\033[0m"

# define ERR_ARGS_NR	"ERROR: Expected 4 or 5 arguments.\n"
# define ERR_ARGS_VAL	"ERROR: Arguments must be integers >= 0.\n"
# define ERR_TR_CREATE	"ERROR: pthread_create() failed."
# define ERR_TR_JOIN	"ERROR: pthread_join() failed."

#endif
