#include "functions_p.h"



void iso_diffusion_denoising_parallel(image *u, image *u_bar, float kappa, int iters, int my_rank, int num_procs){
    size_t i, j, k;
    int n = u->n, m = u->m, isEven;

    float* buffer_top = malloc(n*sizeof(float));
    float* buffer_bot = malloc(n*sizeof(float));
    //memset(buffer_top , 0, n*sizeof(float));
    //memset(buffer_bot , 0, n*sizeof(float));
    
    //printf("%d , %d\n",n, my_rank);
    
    image *temp;
    for (int i = 0; i<m; i++) memcpy(u_bar->image_data[i], u->image_data[i],n*sizeof(float));

    // Calculate iters # iterations of algorithm.
    for ( k = 1; k<iters; k++ ){
        isEven = my_rank %2 == 0;
        // Before algorithm we send and recive the row over and/or under us, differentiating
        // if the rank is 0 (only under), even or odd (under and over) or the last rank(only over).
        if(isEven){
                MPI_Send(u->image_data[m-1], n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD);
                if (my_rank != 0 && my_rank != num_procs-1){
                    MPI_Recv(buffer_top, n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    MPI_Send(u->image_data[0], n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD);
                }
                MPI_Recv(buffer_bot, n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
       
        if (!isEven || my_rank ==  num_procs-1)   { 
            MPI_Recv(buffer_top, n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (my_rank != num_procs-1) {
                MPI_Send(u->image_data[m-1], n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD);
                MPI_Recv(buffer_bot, n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
            MPI_Send(u->image_data[0], n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD);
        }
    
        for (i = 1; i<m-1; i++)
            for (j = 1; j<n-1; j++)
                u_bar->image_data[i][j] = u->image_data[i][j] 
                            + kappa*(u->image_data[i-1][j] 
                            + u->image_data[i][j-1] 
                            - 4*u->image_data[i][j] 
                            + u->image_data[i][j+1] 
                            + u->image_data[i+1][j]);
        // For all but the first rank we use the halos to fill in all borders over. 
        if (my_rank > 0) {
            for (j = 1; j<n-1; j++)
                u_bar->image_data[0][j] = u->image_data[0][j] 
                            + kappa*(buffer_top[j] 
                            + u->image_data[0][j-1] 
                            - 4*u->image_data[0][j] 
                            + u->image_data[0][j+1] 
                            + u->image_data[1][j]);
        }
        // For all but the last rank we use the halos to fill in all borders under. 
        if (my_rank < num_procs-1) {
            for (j = 1; j<n-1; j++)
                u_bar->image_data[m-1][j] = u->image_data[m-1][j] 
                            + kappa*(u->image_data[m-2][j] 
                            + u->image_data[m-1][j-1] 
                            - 4*u->image_data[m-1][j] 
                            + u->image_data[m-1][j+1] 
                            + buffer_bot[j]);
        }

        // Update u and u_bar
        MPI_Barrier(MPI_COMM_WORLD);
        if (k < iters-1) {
            temp = u;
            u = u_bar;
            u_bar = temp;
        }
    }
    free(buffer_bot);
    free(buffer_top);
}
