/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:21:56 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/18 16:20:10 by aschenk          ###   ########.fr       */
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
# include <pthread.h> // thread fcts, like pthread_create()

# include "errors.h"

typedef struct s_data
{
	int				nr_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nr_meals;
	int				nr_meals_set;
	pthread_mutex_t	mtx;
}	t_data;

int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);

// utils/check_args.c

int		check_args(int argc, char **argv);
void	print_err_msg(char *msg, char *color, int newline);

void	init_data_struct(t_data *data, int argc, char **argv);

#endif
