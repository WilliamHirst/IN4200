#include "functions.h"


void allocate_image(image *u, int m, int n){
    u->m = m; u->n = n;
    //Allocate the image array.
    u->image_data = malloc(m*sizeof(float*));
    for(int i = 0; i<m;i++) u->image_data[i] = malloc(n*sizeof(float));
}

void deallocate_image(image *u){
    //Deallocate the image array.
    for(int i=0; i<u->m;i++) free(u->image_data[i]);
    free(u->image_data);
}

void convert_jpeg_to_image(const unsigned char* image_chars, image *u){
    size_t i, j;
    //Converts jpeg-array to the image-array.
    for (i = 0; i<u->m; i++)
        for (j = 0; j<u->n; j++){
            u->image_data[i][j] = image_chars[idx(i, j,u->n)];
        }
}

void convert_image_to_jpeg(const image *u, unsigned char* image_chars){
    size_t i, j;
    //Converts image-array to the jpeg-array.
    for (i = 0; i<u->m; i++)
        for (j = 0; j<u->n; j++)
            image_chars[idx(i, j, u->n)] = u->image_data[i][j];
}

void swap( float **p, float **q )
{
    float *tmp = *p;
    *p = *q;
    *q = tmp;
}



void iso_diffusion_denoising_parallel(image *u, image *u_bar, float kappa, int iters, int my_rank, int num_procs){
    size_t i, j, k;
    int n = u->n, m = u->m;

    float* buffer_top = malloc(n*sizeof(float));
    float* buffer_bot = malloc(n*sizeof(float));

    // Calculate iters # iterations of algorithm.
    for ( k = 1; k<iters; k++ ){
        if(my_rank == 0){
                MPI_Send(u->image_data[m-1], n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD);
                MPI_Recv(buffer_bot, n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        if(my_rank > 0 && my_rank < num_procs-1) {
            MPI_Send(u->image_data[m-1], n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD);
            MPI_Recv(buffer_bot, n, MPI_FLOAT, my_rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(u->image_data[0], n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD);
            MPI_Recv(buffer_top, n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        if(my_rank == num_procs - 1){
                MPI_Recv(buffer_top, n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(u->image_data[0], n, MPI_FLOAT, my_rank - 1, 0, MPI_COMM_WORLD);
        }
        MPI_Barrier(MPI_COMM_WORLD);
        for (i = 1; i<m-1; i++)
            for (j = 1; j<n-1; j++)
                u_bar->image_data[i][j] = u->image_data[i][j] 
                            + kappa*(u->image_data[i-1][j] 
                            + u->image_data[i][j-1] 
                            - 4*u->image_data[i][j] 
                            + u->image_data[i][j+1] 
                            + u->image_data[i+1][j]);

        if (my_rank > 0) {
            for (j = 1; j<n-1; j++)
                u_bar->image_data[0][j] = u->image_data[0][j] 
                            + kappa*(buffer_top[j] 
                            + u->image_data[0][j-1] 
                            - 4*u->image_data[0][j] 
                            + u->image_data[0][j+1] 
                            + u->image_data[1][j]);
        }
        if (my_rank > 0) {
            for (j = 1; j<n-1; j++)
                u_bar->image_data[m-1][j] = u->image_data[m-1][j] 
                            + kappa*(u->image_data[m-2][j] 
                            + u->image_data[m-1][j-1] 
                            - 4*u->image_data[m-1][j] 
                            + u->image_data[m-1][j+1] 
                            + buffer_bot[j]);
        }

        // Update u and u_bar

        if (k < iters-1) {
            swap(u->image_data, u_bar->image_data);
        }
    }
    free(buffer_bot);
    free(buffer_top);
   
}
