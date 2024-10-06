/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 18:47:34 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/06 06:22:05 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dining(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_action(get_time() - philo->sim->t_start_sim, philo, FORK);
	print_action(get_time() - philo->sim->t_start_sim, philo, EAT);
	precise_wait(philo->sim->t_eat);
	print_action(get_time() - philo->sim->t_start_sim, philo, SLEEP);
	precise_wait(philo->sim->t_sleep);
	print_action(get_time() - philo->sim->t_start_sim, philo, THINK);
	precise_wait(50);
	print_action(get_time() - philo->sim->t_start_sim, philo, DIE);
	if (FULL != 0)
		print_action(get_time() - philo->sim->t_start_sim, philo, STUFFED);
	return (NULL);
}
