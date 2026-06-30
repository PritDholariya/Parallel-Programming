#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int send_value, recv_value;
    int left, right;

    MPI_Request request;

    double start_time, end_time;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    left = (rank - 1 + size) % size;
    right = (rank + 1) % size;

    send_value = rank;

    MPI_Barrier(MPI_COMM_WORLD);

    start_time = MPI_Wtime();

    MPI_Isend(&send_value,
              1,
              MPI_INT,
              right,
              0,
              MPI_COMM_WORLD,
              &request);

    MPI_Recv(&recv_value,
             1,
             MPI_INT,
             left,
             0,
             MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);

    MPI_Wait(&request,
             MPI_STATUS_IGNORE);

    end_time = MPI_Wtime();

    printf("Rank %d received value %d from Rank %d\n",
           rank,
           recv_value,
           left);

    if(rank == 0)
    {
        printf("Communication Time = %f seconds\n",
               end_time - start_time);
    }

    MPI_Finalize();

    return 0;
}