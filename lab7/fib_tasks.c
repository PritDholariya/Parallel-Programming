#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


long fib_task(int n, int cutoff)
{
    if (n < 2)
        return n;

    if (n <= cutoff)
        return fib_task(n - 1, cutoff) + fib_task(n - 2, cutoff);

    long x, y;

    #pragma omp task shared(x) firstprivate(n, cutoff)
    x = fib_task(n - 1, cutoff);

    #pragma omp task shared(y) firstprivate(n, cutoff)
    y = fib_task(n - 2, cutoff);

    #pragma omp taskwait

    return x + y;
}


long fib_serial(int n)
{
    if (n < 2)
        return n;

    return fib_serial(n - 1) + fib_serial(n - 2);
}


int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <n> <threads> <cutoff>\n", argv[0]);
        return 1;
    }


    int n = atoi(argv[1]);
    int threads = atoi(argv[2]);
    int cutoff = atoi(argv[3]);


    omp_set_num_threads(threads);


    double start_serial = omp_get_wtime();

    long serial_result = fib_serial(n);

    double end_serial = omp_get_wtime();



    long parallel_result;

    double start_parallel = omp_get_wtime();


    #pragma omp parallel
    {
        #pragma omp single
        {
            parallel_result = fib_task(n, cutoff);
        }
    }


    double end_parallel = omp_get_wtime();



    printf("Fib(%d) = %ld\n", n, parallel_result);

    printf("\nThreads : %d", threads);
    printf("\nCutoff  : %d\n", cutoff);


    printf("\nSerial Time   : %f sec\n",
           end_serial - start_serial);


    printf("Parallel Time : %f sec\n",
           end_parallel - start_parallel);


    printf("Speedup       : %.2f\n",
           (end_serial - start_serial) /
           (end_parallel - start_parallel));



    return 0;
}