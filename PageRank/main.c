#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include "read_graph_from_file.c"
#include "PageRank_iterations.c"
#include "top_n_webpages.c"


int main(int argc, char* argv[]){
    double epsilon;
    double d;
    int  N, n;
    char *filename;
    int *row_ptr, *col_idx;
    double *val;
    
    filename = argv[1];
    d = atof(argv[2]);
    epsilon =  atof(argv[3]);
    n = atoi(argv[4]);

    printf("- - - - - - - - - - - - - - - -\n");
    read_graph_from_file(filename, &N, &row_ptr, &col_idx, &val);

    double *scores = malloc(N*sizeof(double)); 
    
    for (size_t i = 0; i < N; i++) scores[i] = (double)1./N;
    
    PageRank_iterations(N, row_ptr,  col_idx,  val, d, epsilon, scores);

    

    top_n_webpages(N, scores, n);


    free(row_ptr);
    free(val);
    free(col_idx);
    
    return 0;
}