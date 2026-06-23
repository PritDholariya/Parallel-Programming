#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define PING_PONG_LIMIT 10

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

    int ping_pong_count = 1;

    double start_time = MPI_Wtime();

    while (ping_pong_count <= PING_PONG_LIMIT)
{
    if (rank == 0)
    {
        MPI_Send(&ping_pong_count, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Rank 0 sent %d to Rank 1\n", ping_pong_count);

        ping_pong_count++;

        if (ping_pong_count > PING_PONG_LIMIT)
            break;

        MPI_Recv(&ping_pong_count, 1, MPI_INT, 1, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Rank 0 received %d from Rank 1\n", ping_pong_count);

        ping_pong_count++;
    }
    else
    {
        MPI_Recv(&ping_pong_count, 1, MPI_INT, 0, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Rank 1 received %d from Rank 0\n", ping_pong_count);

        ping_pong_count++;

        if (ping_pong_count > PING_PONG_LIMIT)
            break;

        MPI_Send(&ping_pong_count, 1, MPI_INT, 0, 0,
                 MPI_COMM_WORLD);

        printf("Rank 1 sent %d to Rank 0\n", ping_pong_count);

        ping_pong_count++;
    }
}

    double end_time = MPI_Wtime();

    if (rank == 0)
    {
        printf("\nElapsed time = %f seconds\n",
               end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}