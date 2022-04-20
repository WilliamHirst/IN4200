#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define idx(i, j,n) i*n + j 
typedef struct
{
    float** image_data; /* a 2D array of floats */
    int m; /* # pixels in vertical-direction */
    int n; /* # pixels in horizontal-direction */
}
image;
    void iso_diffusion_denoising_parallel(image *u, image *u_bar, float kappa, int iters, int my_rank, int num_procs);

#endif
