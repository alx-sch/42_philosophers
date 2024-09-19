/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:21:56 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/19 22:53:53 by aschenk          ###   ########.fr       */
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

int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);

// utils/check_args.c

int		check_args(int argc, char **argv);

void	print_usage(void);
void	print_err_msg(char *msg, t_data *data);

int		init(t_data *data, int argc, char **argv);

int		mtx_act(t_mtx *mutex, t_mtx_act action);

#endif
