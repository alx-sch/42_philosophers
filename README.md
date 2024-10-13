# 42_philosophers

<p align="center">
    <img src="https://github.com/alx-sch/42_philosophers/blob/main/.assets/philosophers_badge.png" alt="philosophers_badge.png" />
</p>

## Comparing `usleep` with a Custom Wait Function
I have implemented a custom wait function to address common issues with `usleep`, such as inconsistent delays. To illustrate the performance differences, I have included a test script: `test_usleep.c`.

You can use this script to compare the performance of `usleep()` and the custom wait function. The script measures the accuracy and consistency of both functions over multiple runs.

To compile and run the test, use the following command:
```bash
cc test_usleep.c -lm -o test_usleep
./test_usleep
```

<img src="https://github.com/alx-sch/42_philosophers/blob/main/.assets/usleep_test_run.png" alt="usleep_test_run.png" width="400" />

### Why a Custom Wait Function?
In real-time simulations, precise timing is crucial, as even small inaccuracies can lead to undesired behavior, especially when multiple threads interact and delays accumulate. The standard `usleep()` function may introduce unexpected delays because of how the operating system handles process scheduling, resulting in less precise timing.

By actively checking the current time and using short sleep intervals, a custom wait function can mitigate these timing issues, resulting in more consistent and reliable behavior. This approach is especially important in scenarios like the Dining Philosophers problem, where precise timing and synchronization between threads are essential to avoid deadlocks and ensure proper execution.

```C
int	precise_wait(int duration_to_wait)
{
	t_ull	time_stop_waiting;
	t_ull	current_time;

	time_stop_waiting = get_time();
	if (time_stop_waiting == 0)
		return (1);
	time_stop_waiting += duration_to_wait;
	while (1)
	{
		current_time = get_time();
		if (current_time == 0)
			return (1);
		if (current_time >= time_stop_waiting)
			break ;
		(void)usleep((duration_to_wait * 1000) / SLEEP_INTERVALS);
	}
	return (0);
}
```

### How `precise_wait` Works
The `precise_wait` function uses a combination of high-resolution time checks and short sleep intervals to provide a more accurate waiting period:

- **Time Measurement**: It starts by determining the current time using  `get_time()`, then calculates the target time ( `time_stop_waiting`) when the waiting period should end.

- **Short Sleep Intervals**: Instead of relying on a single long  `usleep()` call, which may be affected by system scheduling,  `precise_wait` uses short sleep intervals. This approach reduces the chance of oversleeping because it frequently checks the current time.   

- **Continuous Checking**: The function continuously checks if the current time has reached or surpassed  `time_stop_waiting`. This ensures that the wait duration is as precise as possible. The  `SLEEP_INTERVALS` constant controls how frequently the function checks the current time, striking a balance between accuracy and CPU usage.

  
