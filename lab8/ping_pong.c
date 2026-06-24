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
        if ((ping_pong_count % 2 == 1 && rank == 0) ||
            (ping_pong_count % 2 == 0 && rank == 1))
        {
            int receiver = 1 - rank;

            MPI_Send(&ping_pong_count,
                    1,
                    MPI_INT,
                    receiver,
                    0,
                    MPI_COMM_WORLD);

            printf("Rank %d sent ping_pong_count %d to Rank %d\n",
                rank,
                ping_pong_count,
                receiver);
        }
        else
        {
            int sender = 1 - rank;

            MPI_Recv(&ping_pong_count,
                    1,
                    MPI_INT,
                    1,
                    MPI_ANY_TAG,
                    MPI_COMM_WORLD,
                    MPI_STATUS_IGNORE);

            printf("Rank %d received ping_pong_count %d from Rank %d\n",
                rank,
                ping_pong_count,
                sender);
        }

        ping_pong_count++;  
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


//mpicc -O2 -Wall -Wextra -o ping_pong ping_pong.c
//mpirun -n 2 ./ping_pong