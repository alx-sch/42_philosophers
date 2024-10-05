/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:21:56 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/05 13:50:53 by aschenk          ###   ########.fr       */
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

//

// utils/libft.c

int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
int		contains_digit(const char *str);

// utils/check_args.c

int		check_args(int argc, char **argv);
void	*routine(void *arg);

// utils/time.c

t_ull	get_time(void);
void	precise_wait(int duration_to_wait);

void	print_usage(void);
void	print_err_and_clean(char *msg, t_sim *sim);
int		print_action(t_ull timestamp, t_action action, t_philo *philo);

int		init_sim(t_sim *sim, int argc, char **argv);

int		mtx_act(t_mtx *mutex, t_mtx_act action, t_sim *sim);

void	cleanup_sim(t_sim *sim);

#endif
