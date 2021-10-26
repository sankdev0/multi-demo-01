#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <chrono>

#define CHUNKSIZE 1000
#define N 10000000

using namespace std::chrono;

int demo_for_vector(void)
{
	int i, chunk;
	double* a = new double[N + 1];
	double* b = new double[N + 1];
	double* c = new double[N + 1];

	/* Some initializations */
	for (i = 0; i < N; i++)
		a[i] = b[i] = (double)i;
	chunk = CHUNKSIZE;

	printf("Расчет в 2 потоках.");

	// Get starting timepoint
	auto start = high_resolution_clock::now();

#pragma omp parallel num_threads(2) shared(a,b,c,chunk) private(i)
	{
#pragma omp for schedule(dynamic,chunk) nowait
		for (i = 0; i < N; i++) {
			c[i] = a[i] + b[i];
			//printf("I'm thread %d. Calculate %d iteration\n", omp_get_thread_num(), i);
		}
	}  /* end of parallel section */

	// Get ending timepoint
	auto stop = high_resolution_clock::now();

	// Get duration. Substart timepoints to 
	// get durarion. To cast it to proper unit
	// use duration cast method
	auto duration = duration_cast<microseconds>(stop - start);

	printf("===>>> Обработка цикла заняла %lld микросекунд.", (long long)duration.count());

	return 0;
}