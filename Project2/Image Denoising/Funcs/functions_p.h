#ifndef FUNCTIONS_P_H
#define FUNCTIONS_P_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"
#include <mpi.h>


    void iso_diffusion_denoising_parallel(image *u, image *u_bar, float kappa, int iters, int my_rank, int num_procs);

#endif
