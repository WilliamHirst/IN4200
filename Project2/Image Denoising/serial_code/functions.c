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
            //printf("%ld, %ld \n", i,j);
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



void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters){
    size_t i, j, k;
    int n = u->n, m = u->m;
    image buffer;
    allocate_image(&buffer, m,n);

    // Calculate iters # iterations of algorithm.
    for ( k = 1; k<iters; k++ ){
        for (i = 1; i<m-1; i++)
            for (j = 1; j<n-1; j++)
                u_bar->image_data[i][j] = u->image_data[i][j] 
                            + kappa*(u->image_data[i-1][j] 
                            + u->image_data[i][j-1] 
                            - 4*u->image_data[i][j] 
                            + u->image_data[i][j+1] 
                            + u->image_data[i+1][j]);
        // Update u and u_bar
        if (k < iters-1) {
            swap(u->image_data, u_bar->image_data);
        }
    }
    deallocate_image(&buffer);
   
}
