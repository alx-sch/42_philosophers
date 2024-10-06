/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:26:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/06 09:21:07 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
TBD
*/

int	main(int argc, char **argv)
{
	t_sim	*sim;

	sim = NULL;
	if (init_sim(&sim, argc, argv))
	{
		cleanup_sim(&sim);
		return (1);
	}
	if (run_sim(sim))
	{
		cleanup_sim(&sim);
		return (1);
	}
	cleanup_sim(&sim);
	return (0);
}
