#include <stdio.h> // printf()
#include <unistd.h> // usleep()
#include <sys/time.h> // gettimeofday()
#include <math.h> // sqrt()

#define SLEEP_INTVL 100000

/**
Get the current time in milliseconds since the epoch (January 1, 1970).

 @param sim 	Pointer to a data struct to be freed in case of error.

 @return 		The current time in microseconds (us);
				`0` in case of an error (or it's 00:00 AM on 1/1/1970...)
*/
unsigned long long	get_time(void)
{
	struct timeval		tv;
	long long	time_in_ms;

	if (gettimeofday(&tv, NULL))
		return (0);
	time_in_ms = (tv.tv_sec * 1000000) + (tv.tv_usec);
	return (time_in_ms);
}

/**
Halts execution for a specified duration by checking passed time directly at
regular intervals (here: 1000 intervals).

 @param	duration_to_wait 	Duration in microseconds for which to wait.

 @return					`0` if the wait was successful;
							`1` if there was an error retrieving the time.
*/
int	precise_wait(int duration_to_wait)
{
	unsigned long long	time_stop_waiting;
	unsigned long long	current_time;

	time_stop_waiting = get_time();
	if (time_stop_waiting == -1)
		return (1);
	time_stop_waiting += duration_to_wait;
	while (1)
	{
		current_time = get_time();
		if (current_time == 0)
			return (1);
		if (current_time >= time_stop_waiting)
			break ;
		usleep((duration_to_wait) / SLEEP_INTVL);
	}
	return (0);
}

void	test_wait(void *func_ptr, int sleep_duration_us, int iterations)
{
	unsigned long long	total_time;
	unsigned long long	min_time;
	unsigned long long	max_time;
	unsigned long long	time_before;
	unsigned long long	elapsed_time;
	unsigned long long	elapsed_times[iterations];
	double		average_time;
	double		variance;
	double		stddev;
	int			i;

	total_time = 0;
	min_time = -1;
	max_time = 0;

	i = 0;
	while (i < iterations)
	{
		time_before = get_time();

		((void (*)(int))func_ptr)(sleep_duration_us); // pass sleep duration in microsec to wait fct

		elapsed_time = get_time() - time_before;
		elapsed_times[i] = elapsed_time;
		total_time += elapsed_time;

		if (elapsed_time < min_time)
			min_time = elapsed_time;
		if (elapsed_time > max_time)
			max_time = elapsed_time;
		i++;
	}

	average_time = (double)total_time / iterations;

	// Calculate standard deviation
	variance = 0.0;
	i = 0;
	while (i < iterations)
	{
		variance += ((double)elapsed_times[i] - average_time)
			* ((double)elapsed_times[i] - average_time);
		i++;
	}
	variance /= iterations;
	stddev = sqrt(variance);

	printf("Average time elapsed (%d us; %d iterations): %.2f us\n",
		sleep_duration_us, iterations, average_time);
	printf("Range: min = %llu us, max = %llu us\n", min_time, max_time);
	printf("Standard deviation: %.2f us\n", stddev);
}


int	main(void)
{
	int	sleep_duration; // in microseconds
	int	iterations;

	sleep_duration = 300 * 1000;
	iterations = 100;

	printf("++ TESTING usleep ++\n");
	test_wait((void *)usleep, sleep_duration, iterations);

	printf("\n");

	printf("++ TESTING precise_wait ++\n");
	printf("Sleep intervals: %d\n", SLEEP_INTVL);
	test_wait((void *)precise_wait, sleep_duration, iterations);
	return (0);
}
