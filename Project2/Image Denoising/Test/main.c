#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int my_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    printf("Hello from process %d\n", my_rank);
    MPI_Finalize();
}

if(my_rank == 0){
                MPI_Send(u->image_data[m-1], n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD);
                MPI_Recv(buffer_bot, n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        if (my_rank %2 == 0 &&  my_rank != 0 && my_rank != num_procs-1) { 
            MPI_Send(u->image_data[m-1], n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD);
            MPI_Recv(buffer_top, n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(u->image_data[0], n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD);
            MPI_Recv(buffer_bot, n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        if (my_rank %2 != 0 &&  my_rank != 0 && my_rank != num_procs-1)  { 
            MPI_Recv(buffer_top, n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(u->image_data[m-1], n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD);
            MPI_Recv(buffer_bot, n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(u->image_data[0], n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD);
        }

        if(my_rank == num_procs - 1){
                MPI_Recv(buffer_top, n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(u->image_data[0], n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD);
        }
