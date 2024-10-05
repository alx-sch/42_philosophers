/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:21:56 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/05 17:57:23 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
TBD
*/

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // perror(), printf()
# include <string.h> // memset()
# include <stdlib.h> // malloc(), free()
# include <unistd.h> // write(), usleep()
# include <sys/time.h> // gettimeofday()

# include "errors.h"
# include "types.h" // all data structure types, e.g. 't_data'

// Used in precise_wait()
# define SLEEP_INTERVALS 100

// 1_check_args.c

int		check_args(int argc, char **argv);

// 1_init_sim.c

int		init_sim(t_sim **sim, int argc, char **argv);


int		start_sim(t_sim *sim);

// utils/0_libft.c

int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
int		contains_digit(const char *str);

// utils/1_print_action.c

int		print_action(t_philo *philo, t_action action, t_ull timestamp);

// utils/1_print_misc.c

void	print_usage(void);
void	print_err_and_clean(char *msg);

// utils/2_mutex.c

int		mtx_act(t_mtx *mutex, t_mtx_act action);

// utils/3_time.c

t_ull	get_time(void);
int		precise_wait(int duration_to_wait);

// utils/X_free.c

void	cleanup_sim(t_sim **sim_ptr);



void	*routine(void *arg);


#endif
