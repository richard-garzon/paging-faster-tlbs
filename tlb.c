#include <bits/time.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main()
{
	int page_size = 4096;
	int jump = page_size / sizeof(int);
	int num_trials = 10000000;
	int NUMPAGES = 32;
	int a[NUMPAGES * jump];

	// init array to 0 to avoid demand paging showing up in loop
	memset(a, 0, NUMPAGES * jump);

	struct timespec start, end;

	// TODO: pin this thread to a single CPU

	clock_gettime(CLOCK_MONOTONIC, &start);

	// making j volatile should keep the compiler from optimizing away the outer
	// loop ew outer loop is j but too lazy to fix
	volatile int j;
	for (j = 0; j < num_trials; j++)
	{
		for (int i = 0; i < NUMPAGES * jump; i += jump)
		{
			a[i] += 1;
		}
	}

	clock_gettime(CLOCK_MONOTONIC, &end);

	printf("Done\n");

	long time_seconds = end.tv_sec - start.tv_sec;
	long time_nanoseconds = end.tv_nsec - start.tv_nsec;

	double elapsed_ns = time_seconds * 1000000000L + time_nanoseconds;
	double average_time = elapsed_ns / jump / num_trials;

	printf("Average nanoseconds per access for %d pages: %f\n", NUMPAGES,
		   average_time);
}
