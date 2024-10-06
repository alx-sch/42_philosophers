/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:21:56 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/06 22:06:09 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
The primary header file for the dining philosopher simulation.

As it aggregates all necessary headers and declarations, `philo.h` ensures
that each source file within the project has access to all definitions without
redundant includes.
*/

#ifndef PHILO_H
# define PHILO_H

# include "types.h" // All custom types and data structs, e.g. 't_sim'
# include "errors.h" // Error messages and respective formatting

# include <stdio.h> // perror(), printf()
# include <string.h> // memset()
# include <stdlib.h> // malloc(), free()
# include <unistd.h> // write(), usleep()
# include <sys/time.h> // gettimeofday()

//	+++++++++++++++
//	++ CONSTANTS ++
//	+++++++++++++++

/**
Used in `precise_wait()` to divide the total wait time into smaller sleep
intervals.

Precision vs. CPU Load Trade-off:
 -	Larger SLEEP_INTERVALS (smaller sleep durations): Higher precision, but
	increased CPU usage.
 -	Smaller SLEEP_INTERVALS (larger sleep durations): Reduced precision, but
 	lower CPU usage.

If `SLEEP_INTERVALS = 1`, the behavior would be similar to a direct call to
`usleep()`, without the added precision checks.
*/
# define SLEEP_INTERVALS 1000000000

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

// 1_check_args.c

int		check_args(int argc, char **argv);

// 2_init_sim.c

int		init_sim(t_sim **sim, int argc, char **argv);

// 3_run_sim.c

int		run_sim(t_sim *sim);

// X_dining.c

void	*dining(void *arg);
void	*monitoring(void *arg);

// utils/0_libft.c

int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
int		contains_digit(const char *str);

// utils/1_print_action.c

int		print_action(t_ull timestamp, t_philo *philo, t_action action,
			int recalc_timestamp);

// utils/1_print_error.c

void	print_err_msg(char *msg);
void	print_usage(void);

// utils/2_mutex.c

int		mtx_action(t_mtx *mutex, t_mtx_action action);

// utils/3_time.c

t_ull	get_time(void);
int		set_start_time(t_sim *sim);
int		record_time_of_death(t_philo *philo);
int		precise_wait(int duration_to_wait);

// utils/X_free.c

void	cleanup_sim(t_sim **sim_ptr);

#endif
