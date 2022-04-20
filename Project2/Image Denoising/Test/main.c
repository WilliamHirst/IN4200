#include <stdio.h>
#include "/usr/local/opt/open-mpi/include/mpi.h"

int main(int argc, char* argv[])
{
    int my_rank;
    printf("fadsnfasjdf\n");
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    printf("Hello from process %d\n", my_rank);
    MPI_Finalize();
}
