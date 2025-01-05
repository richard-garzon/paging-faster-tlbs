#define _GNU_SOURCE
#include <bits/time.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv)
{

	if (argc < 2)
	{
		printf("Not enough args passed. First arg is num trials and second is "
			   "num pages\n");
	}

	int page_size = getpagesize();
	int jump = page_size / sizeof(int);

	int num_trials = atoi(argv[1]);
	int num_pages = atoi(argv[2]);

	int *a = calloc(num_pages, page_size);

	struct timespec start, end;

	// pin this thread to a single CPU
	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(0, &set);
	sched_setaffinity(0, sizeof(cpu_set_t), &set);

	clock_gettime(CLOCK_MONOTONIC, &start);

	// making j volatile should keep the compiler from optimizing away the outer
	// loop ew outer loop is j but too lazy to fix
	volatile int j;
	for (j = 0; j < num_trials; j++)
	{
		for (int i = 0; i < num_pages * jump; i += jump)
		{
			a[i] += 1;
		}
	}

	clock_gettime(CLOCK_MONOTONIC, &end);
	long time_seconds = end.tv_sec - start.tv_sec;
	long time_nanoseconds = end.tv_nsec - start.tv_nsec;

	double elapsed_ns = time_seconds * 1000000000L + time_nanoseconds;
	double average_time = elapsed_ns / ((double)num_pages * num_trials);

	/*
	printf("Average nanoseconds per access for %d pages: %f\n", num_pages,
		   average_time);
	printf("Total elapsed time in nanoseconds for %d pages: %f\n", num_pages,
		   (elapsed_ns / num_trials));
	*/

	// print just the average ns per access so the python script can easily
	// parse this
	printf("%f", average_time);

	return 0;
}
