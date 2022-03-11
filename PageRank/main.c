#include <stdio.h>
#include <stdlib.h>
#include "read_graph_from_file.c"

int main(int argc, char* argv[]){
    //double d, epsilon;
    //int n;//, *N;
    char *filename;
    //int **row_ptr, **col_idx;
    //double **val;
    filename = argv[1];
    //d = atof(argv[2]);
    //epsilon =  atof(argv[3]);
    //n = atoi(argv[4]);

    read_graph_from_file(filename);//, N, row_ptr, col_idx, val);
}