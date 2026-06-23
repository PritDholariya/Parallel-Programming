#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


#define SIZE 100000000


long long sum_taskloop(int *array, int n, int grainsize)
{
    long long sum = 0;


    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp taskloop reduction(+:sum) grainsize(grainsize)
            for(int i = 0; i < n; i++)
            {
                sum += array[i];
            }
        }
    }


    return sum;
}



long long sum_parallel_for(int *array, int n)
{
    long long sum = 0;


    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++)
    {
        sum += array[i];
    }


    return sum;
}



int main(int argc, char *argv[])
{

    if(argc != 3)
    {
        printf("Usage: %s <threads> <grainsize>\n", argv[0]);
        return 1;
    }


    int threads = atoi(argv[1]);
    int grainsize = atoi(argv[2]);


    omp_set_num_threads(threads);



    int *array = malloc(sizeof(int) * SIZE);


    srand(42);


    for(int i=0;i<SIZE;i++)
    {
        array[i] = rand() % 100;
    }



    double start, end;


    // taskloop

    start = omp_get_wtime();

    long long task_sum =
        sum_taskloop(array, SIZE, grainsize);

    end = omp_get_wtime();


    double task_time = end-start;



    // parallel for

    start = omp_get_wtime();

    long long for_sum =
        sum_parallel_for(array, SIZE);

    end = omp_get_wtime();


    double for_time = end-start;



    printf("Array size : %d\n", SIZE);
    printf("Threads    : %d\n", threads);
    printf("Grainsize  : %d\n\n", grainsize);


    printf("Taskloop result : %lld\n", task_sum);
    printf("Taskloop time   : %f sec\n\n", task_time);


    printf("Parallel for result : %lld\n", for_sum);
    printf("Parallel for time   : %f sec\n", for_time);



    if(task_sum == for_sum)
        printf("\nResults match\n");
    else
        printf("\nERROR\n");


    free(array);


    return 0;
}