#include "functions.h"

int main(int argc, char *argv[])
{
    printf("hfabdsfhbasdhfbahjsbf\n");
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
    }
    MPI_Bcast (&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast (&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    /* 2D decomposition of the m x n pixels evenly among the MPI processes */
    printf("hfabdsfhbasdhfbahjsbf %d\n", n);
    exit(0);
    my_m = m/num_procs;
    my_n = n/num_procs;
    if (my_rank ==0){
        my_m += m%num_procs;
        my_n += n%num_procs;
    }


    my_N = my_m + my_n;
 
    my_image_chars = malloc(my_N * sizeof(float));

    int *chunk_sizes = malloc(num_procs*sizeof(*chunk_sizes));


    MPI_Gather(&my_N, 1, MPI_INT, &chunk_sizes[my_rank], 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    int *displ = malloc(num_procs*sizeof(*displ));

    displ[0] = 0;
    for(int i = 1; i < num_procs; i++){
        displ[i] = i*chunk_sizes[i-1];
    }

    MPI_Scatterv(image_chars, &my_N, displ, MPI_UNSIGNED_CHAR, my_image_chars, my_N, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    
    MPI_Barrier(MPI_COMM_WORLD);

    allocate_image (&u, my_m, my_n);
    allocate_image (&u_bar, my_m, my_n);

    convert_jpeg_to_image (my_image_chars, &u);
    iso_diffusion_denoising_parallel(&u, &u_bar, kappa, iters, my_rank, num_procs);
    convert_image_to_jpeg(&u_bar,  my_image_chars);

    MPI_Barrier(MPI_COMM_WORLD);
    //gather image chars from each process
    MPI_Gatherv(my_image_chars, my_N, MPI_UNSIGNED_CHAR, image_chars, chunk_sizes, displ, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    if (my_rank==0) {
        export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
        free(image_chars);
    }
    deallocate_image (&u);
    deallocate_image (&u_bar);
    MPI_Finalize ();
    return 0;
}