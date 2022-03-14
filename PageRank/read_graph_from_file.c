#include <stdio.h>
#include <stdlib.h>
#include <time.h>



 void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val){
    FILE *fp;
    int edges;
    char *line  = NULL;
    size_t size_line = 32;
    ssize_t reader;
    fp = fopen(filename, "r");
    
    for(int i = 0; i<4; i++){
        reader = getline(&line, &size_line, fp);
        if (i == 1) fscanf(fp, " %*s %*s %d %*s %d", N, &edges);
    }
    printf("Number of nodes: %d --- Number of edges: %d\n", *N, edges);
    printf("- - - - - - - - - - - - - - - -\n");

    *col_idx = malloc(edges*sizeof(int));
    *row_ptr = malloc((*N+1)*sizeof(int));
    *val = malloc(edges*sizeof(double));

    int node_from, node_to, counter, c_indx, r_indx;
    double *col_counter = malloc(*N*sizeof(double));
    int *row_counter = malloc((*N+1)*sizeof(int));
    int *index = malloc(edges*sizeof(int));
    int *added_rows = malloc(*N*sizeof(int));
    int indx;
    
    counter = 0;
    while ((fscanf(fp,"%d %d", &c_indx, &r_indx)) != EOF) {
        col_counter[c_indx] ++;
        row_counter[r_indx] ++;
        counter += 1;
    }
    
    (*row_ptr)[0] = 0;

    for (size_t i = 1; i < *N; i++)
    {
        (*row_ptr)[i] = (*row_ptr)[i-1] + row_counter[i-1];
    }

    (*row_ptr)[*N] = edges;

    rewind(fp);

    //Jump over first 4 lines.
    for(int i = 0; i<4; i++) reader = getline(&line, &size_line, fp);

    counter = 0;
    while ((fscanf(fp,"%d %d", &c_indx, &r_indx)) != EOF) {
        indx = (*row_ptr)[r_indx] + added_rows[r_indx];
        (*col_idx)[indx] = c_indx;
        (*val)[indx] = (double) 1. /col_counter[c_indx];
        added_rows[r_indx] ++;
        counter ++;
    }    
    fclose (fp);

    printf("Hyperlink matrix built: Format -> CRS.\n");
    printf("- - - - - - - - - - - - - - - -\n");
    
    
    free(col_counter);
    free(row_counter);
    free(index);
    free(added_rows);
 }
