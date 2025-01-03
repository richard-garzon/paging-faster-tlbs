#include <stdio.h>
#include <sys/time.h>

int main() {
	int page_size = 4096;
	int jump = page_size / sizeof(int);

	int NUMPAGES = 2;

	int a[NUMPAGES * jump];

	struct timeval tv;
	gettimeofday(&tv, NULL);

	for(int i=0; i < NUMPAGES*jump; i += jump)
	{
		a[i] += 1;
	}

	printf("Done\n");
	printf("Microseconds to run: %ld\n", tv.tv_usec);
}
