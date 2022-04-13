#include <stdlib.h>
#include <stdio.h>
#include <functions.h>
typedef struct
{
    float** image_data; /* a 2D array of floats */
    int m; /* # pixels in vertical-direction */
    int n; /* # pixels in horizontal-direction */
}
image;

void allocate_image(image *u, int m, int n);
    u.m = m; u.n = n;
    u.image_data = malloc(n*sizeof(float*));
    for(int i; i<n;i++) u.image_data[i] = malloc(m*sizeof(float));

void deallocate_image(image *u, int m, int n);
    for(int i; i<n;i++) free(u.image_data[i]);

void deallocate_image(image *u);

void convert_jpeg_to_image(const unsigned char* image_chars, image *u);

void convert_image_to_jpeg(const image *u, unsigned char* image_chars);

void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters);

