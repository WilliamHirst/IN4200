#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define idx(i, j,n)  i*n + j 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    float** image_data; /* a 2D array of floats */
    int m; /* # pixels in vertical-direction */
    int n; /* # pixels in horizontal-direction */
}
image;

    void allocate_image(image *u, int m, int n);
    void deallocate_image(image *u);
    void convert_jpeg_to_image(const unsigned char* image_chars, image *u);
    void convert_image_to_jpeg(const image *u, unsigned char* image_chars);
    void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters);
    void import_JPEG_file (const char* filename, unsigned char** image_chars,
                       int* image_height, int* image_width,
                       int* num_components);
    void export_JPEG_file (const char* filename, const unsigned char* image_chars,
                       int image_height, int image_width,
                       int num_components, int quality);

#endif
