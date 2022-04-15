#include "functions.h"


int main(int argc, char *argv[])
{
    int m, n, c, iters;
    float kappa;
    image u, u_bar;
    unsigned char *image_chars;
    char *input_jpeg_filename, *output_jpeg_filename;
    

    kappa = atof(argv[1]);
    iters = atoi(argv[2]);
    input_jpeg_filename = argv[3];
    output_jpeg_filename = argv[4];
    

    import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
    printf("JPEG imported.\n");
    printf("Pixels -> [W: %d, H: %d]\n", m, n);
    allocate_image (&u, m, n);
    allocate_image (&u_bar, m, n);
    convert_jpeg_to_image (image_chars, &u);
    printf("Calculating iterations...\n");
    iso_diffusion_denoising (&u, &u_bar, kappa, iters);
    printf("%d iterations completed.\n", iters);
    convert_image_to_jpeg (&u_bar, image_chars);
    export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
    printf("Denoised image exported.\n");
    deallocate_image (&u);
    deallocate_image (&u_bar);
    printf("Finished.\n");
    return 0;
}