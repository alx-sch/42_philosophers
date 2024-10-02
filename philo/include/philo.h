/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:21:56 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/26 18:28:41 by aschenk          ###   ########.fr       */
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
# include <stdint.h> // uint64_t

# include "errors.h"
# include "types.h" // all data structure types, e.g. 't_data'

// utils/libft.c

int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
int			contains_digit(const char *str);

// utils/check_args.c

int			check_args(int argc, char **argv);

uint64_t	get_time(void);

void		print_usage(void);
void		print_err_and_clean(char *msg, t_sim *sim);

int			init_sim(t_sim *sim, int argc, char **argv);

int			mtx_act(t_mtx *mutex, t_mtx_act action, t_sim *sim);

void		cleanup_sim(t_sim *sim);

#endif
