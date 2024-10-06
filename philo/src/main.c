/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:26:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/10/06 22:10:46 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <math.h>
/*
TBD
*/

// t_ull	get_time_microsec(void)
// {
// 	struct timeval	tv;
// 	t_ull			time_in_ms;

// 	if (gettimeofday(&tv, NULL))
// 	{
// 		print_err_msg(ERR_GET_TIME);
// 		return (0);
// 	}
// 	time_in_ms = (tv.tv_sec * 1000000) + (tv.tv_usec);
// 	return (time_in_ms);
// }

// void test_usleep(int sleep_duration_us, int iterations)
// {
//     t_ull total_time = 0;
//     t_ull min_time = -1; // Initialize to a large value
//     t_ull max_time = 0;
//     double elapsed_times[iterations]; // Array to store individual elapsed times

//     for (int i = 0; i < iterations; ++i)
//     {
//         t_ull time_before = get_time_microsec();
//         usleep(sleep_duration_us);
//         t_ull elapsed_time = get_time_microsec() - time_before;

//         elapsed_times[i] = (double)elapsed_time; // Store the elapsed time
//         total_time += elapsed_time;

//         // Update min and max
//         if (elapsed_time < min_time)
//             min_time = elapsed_time;
//         if (elapsed_time > max_time)
//             max_time = elapsed_time;
//     }

//     double average_time = (double)total_time / iterations;

//     // Calculate standard deviation
//     double variance = 0.0;
//     for (int i = 0; i < iterations; ++i)
//     {
//         variance += (elapsed_times[i] - average_time) * (elapsed_times[i] - average_time);
//     }
//     variance /= iterations;
//     double stddev = sqrt(variance);

//     printf("Average time elapsed for usleep (%d us): %.2f us\n",
//            sleep_duration_us, average_time);
//     printf("Range: min = %llu us, max = %llu us\n", min_time, max_time);
//     printf("Standard deviation: %.2f us\n", stddev);
// }

// void test_precise_wait(int wait_duration_us, int iterations)
// {
//     t_ull total_time = 0;
//     t_ull min_time = -1; // Initialize to a large value
//     t_ull max_time = 0;
//     double elapsed_times[iterations]; // Array to store individual elapsed times

//     for (int i = 0; i < iterations; ++i)
//     {
//         t_ull time_before = get_time_microsec();
//         precise_wait(wait_duration_us / 1000); // precise_wait takes duration in ms
//         t_ull elapsed_time = get_time_microsec() - time_before;

//         elapsed_times[i] = (double)elapsed_time; // Store the elapsed time
//         total_time += elapsed_time;

//         // Update min and max
//         if (elapsed_time < min_time)
//             min_time = elapsed_time;
//         if (elapsed_time > max_time)
//             max_time = elapsed_time;
//     }

//     double average_time = (double)total_time / iterations;

//     // Calculate standard deviation
//     double variance = 0.0;
//     for (int i = 0; i < iterations; ++i)
//     {
//         variance += (elapsed_times[i] - average_time) * (elapsed_times[i] - average_time);
//     }
//     variance /= iterations;
//     double stddev = sqrt(variance);

//     printf("Average time elapsed for precise_wait (%d us): %.2f us\n",
//            wait_duration_us, average_time);
//     printf("Range: min = %llu us, max = %llu us\n", min_time, max_time);
//     printf("Standard deviation: %.2f us\n", stddev);
// }


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

	// (void)argc;
	// (void)argv;
	// printf("\n\n");
	// int sleep_duration = 300000; // 10,000 microseconds
	// int iterations = 100;

    // printf("\nTesting usleep and precise_wait (%d iterations)\n", iterations);
	// printf("SLEEP_INTERVALS = %d\n\n", SLEEP_INTERVALS);
    // test_usleep(sleep_duration, iterations);
	// printf("\n");
    // test_precise_wait(sleep_duration, iterations);

	// printf("\n\n");

	return (0);
}
