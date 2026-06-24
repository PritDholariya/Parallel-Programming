#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define COUNT 10

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2)
    {
        if (rank == 0)
        {
            printf("Error: Program must be run with exactly 2 processes.\n");
        }

        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == 0)
    {
        int numbers[COUNT];
        int sum;

        for (int i = 0; i < COUNT; i++)
        {
            numbers[i] = i + 1;
        }

        MPI_Send(numbers,
                 COUNT,
                 MPI_INT,
                 1,
                 0,
                 MPI_COMM_WORLD);

        printf("Rank 0 sent array to Rank 1\n");

        MPI_Recv(&sum,
                 1,
                 MPI_INT,
                 1,
                 0,
                 MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

        printf("Rank 0 received sum %d from Rank 1\n", sum);

        printf("Final sum = %d\n", sum);
    }
    else
    {
        int numbers[COUNT];
        int sum = 0;

        MPI_Recv(numbers,
                 COUNT,
                 MPI_INT,
                 0,
                 0,
                 MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

        printf("Rank 1 received array from Rank 0\n");

        for (int i = 0; i < COUNT; i++)
        {
            sum += numbers[i];
        }

        MPI_Send(&sum,
                 1,
                 MPI_INT,
                 0,
                 0,
                 MPI_COMM_WORLD);

        printf("Rank 1 sent sum %d to Rank 0\n", sum);
    }

    MPI_Finalize();

    return 0;
}