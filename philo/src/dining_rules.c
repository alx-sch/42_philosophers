/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 18:47:34 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/05 20:01:46 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dining(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_action(philo, FORK, get_time() - philo->sim->t_start_sim);
	print_action(philo, EAT, get_time() - philo->sim->t_start_sim);
	precise_wait(philo->sim->t_eat);
	print_action(philo, SLEEP, get_time() - philo->sim->t_start_sim);
	precise_wait(philo->sim->t_sleep);
	print_action(philo, THINK, get_time() - philo->sim->t_start_sim);
	precise_wait(50);
	print_action(philo, DIE, get_time() - philo->sim->t_start_sim);
	if (FULL != 0)
		print_action(philo, STUFFED, get_time() - philo->sim->t_start_sim);
	return (NULL);
}
