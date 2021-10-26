#include <omp.h>
#include <stdio.h>
#include "common-header.h"

int demo_shared_private(void)
{
	int rank;

#pragma omp parallel shared(rank) num_threads(3)
	{
		rank = omp_get_thread_num();
		printf("My rank = %d\n", rank);
		if (rank == 0)
			printf("This message is only for private variables!\n");
	}
	return 0;
}