#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <num_steps>\n", argv[0]);
        return 1;
    }

    long num_steps = atol(argv[1]);

    double step = 1.0 / (double)num_steps;

    double sum = 0.0;
    double pi;
    double x;

    double start = omp_get_wtime();

    for(long i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    double end = omp_get_wtime();

    pi = step * sum;

    printf("Approximation of Pi = %.15f\n", pi);

    printf("pi_seq,%ld,1,%f,%.15f\n",
           num_steps,
           end - start,
           pi);

    return 0;
}