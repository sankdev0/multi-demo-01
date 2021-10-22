#include <omp.h>
#include <stdio.h>
#include "common-header.h"

int demoNumThreads(void)
{
#pragma omp parallel num_threads(4)
	{
		printf("Hello, world!\n");
	}
	return 0;
}

int demoThreadsInfo(void)
{
	omp_set_num_threads(6);
	#pragma omp parallel
	{
		int numThreads = omp_get_num_threads();
		printf("Hello, world! I am %u  thread from %u  threads!\n", omp_get_thread_num(), numThreads);
	}
	return 0;
}