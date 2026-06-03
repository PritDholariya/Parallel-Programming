#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <num_steps> <threads>\n", argv[0]);
        return 1;
    }

    long num_steps = atol(argv[1]);
    int threads = atoi(argv[2]);

    omp_set_num_threads(threads);

    double step = 1.0 / (double)num_steps;
    double pi;
    double global_sum = 0.0;

    // Array to store partial sums from each thread
    double *partial_sums = (double *)calloc(threads, sizeof(double));

    if (partial_sums == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    double start_time = omp_get_wtime();

#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();

        // Block decomposition
        long chunk = num_steps / nthreads;

        long start_i = tid * chunk;

        long end_i;
        if (tid == nthreads - 1)
            end_i = num_steps;      // last thread gets remainder
        else
            end_i = start_i + chunk;

        double local_sum = 0.0;

        for (long i = start_i; i < end_i; i++)
        {
            double x = (i + 0.5) * step;
            local_sum += 4.0 / (1.0 + x * x);
        }

        // Store result of this thread
        partial_sums[tid] = local_sum;

        // Wait until all threads finish
        #pragma omp barrier

        // Only thread 0 combines results
        #pragma omp master
        {
            for (int t = 0; t < nthreads; t++)
            {
                global_sum += partial_sums[t];
            }
        }
    }

    double end_time = omp_get_wtime();

    pi = step * global_sum;

    printf("Approximation of Pi = %.15f\n", pi);

    printf("pi_par_master,%ld,%d,%f,%.15f\n",
           num_steps,
           threads,
           end_time - start_time,
           pi);

    free(partial_sums);

    return 0;
}