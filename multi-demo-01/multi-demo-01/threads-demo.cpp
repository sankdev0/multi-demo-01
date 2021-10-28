#include <omp.h>
#include <stdio.h>
#include "common-header.h"

int demo_hello_world(void) {
#pragma omp parallel
	{
		printf("Hello, world!\n");
	}
	return 0;
}

int demo_num_threads(void)
{
#pragma omp parallel num_threads(4)
	{
		printf("Hello, world!\n");
	}
	return 0;
}

int demo_threads_info(void)
{
	omp_set_num_threads(4);
	#pragma omp parallel
	{
		int numThreads = omp_get_num_threads();
		printf("Hello, world! I am %u  thread from %u  threads!\n", omp_get_thread_num(), numThreads);
	}
	return 0;
}