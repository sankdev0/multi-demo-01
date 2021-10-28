#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <chrono>

#define N 10000000

using namespace std::chrono;

int demo_sections(void)
{
	int i;
	double* a = new double[N + 1];
	double* b = new double[N + 1];
	double* c = new double[N + 1];
	double* d = new double[N + 1];

	/* Some initializations */
	for (i = 0; i < N; i++) {
		a[i] = i * 1.5;
		b[i] = i + 22.35;
	}

	auto start = high_resolution_clock::now();

#pragma omp parallel num_threads(2) shared(a,b,c,d) private(i)
	{
#pragma omp sections nowait
		{
#pragma omp section
			{
				for (i = 0; i < N; i++) {
					c[i] = a[i] + b[i];
				}
			}
#pragma omp section
			{
				for (i = 0; i < N; i++) {
					d[i] = a[i] * b[i];
				}
			}
		}  /* end of sections */
	}  /* end of parallel section */

	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);

	printf("===>>> Обработка цикла заняла %lld микросекунд.", (long long)duration.count());

	return 0;
}

int demo_no_sections(void)
{
	int i;
	double* a = new double[N + 1];
	double* b = new double[N + 1];
	double* c = new double[N + 1];
	double* d = new double[N + 1];

	/* Some initializations */
	for (i = 0; i < N; i++) {
		a[i] = i * 1.5;
		b[i] = i + 22.35;
	}

	auto start = high_resolution_clock::now();

	for (i = 0; i < N; i++) {
		c[i] = a[i] + b[i];
	}

	for (i = 0; i < N; i++) {
		d[i] = a[i] * b[i];
	}

	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);

	printf("===>>> Обработка цикла заняла %lld микросекунд.", (long long)duration.count());

	return 0;
}