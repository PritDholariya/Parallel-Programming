#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s <num_steps> <threads>\n", argv[0]);
        return 1;
    }

    long num_steps = atol(argv[1]);
    int threads = atoi(argv[2]);

    omp_set_num_threads(threads);

    double step = 1.0 / (double)num_steps;

    double global_sum = 0.0;
    double pi;

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();

        long chunk = num_steps / nthreads;

        long start_i = tid * chunk;

        long end_i;
        if(tid == nthreads - 1)
            end_i = num_steps;
        else
            end_i = start_i + chunk;

        double local_sum = 0.0;

        for(long i = start_i; i < end_i; i++)
        {
            double x = (i + 0.5) * step;
            local_sum += 4.0 / (1.0 + x * x);
        }

        #pragma omp critical
        {
            global_sum += local_sum;
        }
    }

    double end = omp_get_wtime();

    pi = step * global_sum;

    printf("Approximation of Pi = %.15f\n", pi);

    printf("pi_par,%ld,%d,%f,%.15f\n",
           num_steps,
           threads,
           end - start,
           pi);

    return 0;
}