#include "../Funcs/functions.h"
#include "../Funcs/functions_p.h"

int main(int argc, char *argv[])
{
    int m, n, c, iters;
    int my_m, my_n, my_rank, num_procs, my_N;
    float kappa;
    image u, u_bar;
    unsigned char *image_chars, *my_image_chars;
    char *input_jpeg_filename, *output_jpeg_filename;
    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

    kappa = atof(argv[1]);
    iters = atoi(argv[2]);
    input_jpeg_filename = argv[3];
    output_jpeg_filename = argv[4];

    if (my_rank==0) {
        import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
        printf("JPEG imported.\n");
        printf("Pixels -> [W: %d, H: %d]\n", m, n);
    }
    MPI_Bcast (&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast (&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    my_m = m/num_procs + (my_rank <= m%num_procs-1);
    my_n = n;

    allocate_image (&u, my_m, my_n);
    allocate_image (&u_bar, my_m, my_n);
        
    my_N = my_m * my_n;
    
    my_image_chars = malloc(my_N * sizeof(char));

    //Create variables for scatter of image_chars.
    int *chunk_sizes = malloc(num_procs*sizeof(*chunk_sizes));
    MPI_Gather(&my_N, 1, MPI_INT, &chunk_sizes[my_rank], 1, MPI_INT, 0, MPI_COMM_WORLD);

    int *displ = malloc(num_procs*sizeof(*displ));
    displ[0] = 0;
    for(int i = 1; i < num_procs; i++){
        displ[i] = displ[i-1] + chunk_sizes[i-1];
    }
    
    MPI_Scatterv(image_chars, chunk_sizes, displ, MPI_UNSIGNED_CHAR, my_image_chars, my_N, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
    

    convert_jpeg_to_image (my_image_chars, &u);
    MPI_Barrier(MPI_COMM_WORLD);

    //Calculate the algorithm.
    if (my_rank==0) printf("Calculating iterations...\n");
    iso_diffusion_denoising_parallel(&u, &u_bar, kappa, iters, my_rank, num_procs);
    if (my_rank==0) printf("%d iterations completed.\n", iters);    
    
    //Convert to jpeg and gather image_chars from each process
    convert_image_to_jpeg(&u_bar,  my_image_chars);
    MPI_Gatherv(my_image_chars, my_N, MPI_UNSIGNED_CHAR, image_chars, chunk_sizes, displ, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
    
    //Export full image_chars to output file.
    if (my_rank==0) {
        export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
        printf("Denoised image exported.\n");
        free(image_chars);
    }
    
    //Free upp all arrays.
    deallocate_image (&u);
    deallocate_image (&u_bar);
    free(my_image_chars);
    free(displ);
    free(chunk_sizes);
    MPI_Finalize ();
    if (my_rank==0) printf("\n -------* Finished *------- \n");

    return 0;
}