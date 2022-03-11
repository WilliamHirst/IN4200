#include <stdio.h>
#include <stdlib.h>
#include <read_grap_from_file.c>

int main(int argc, char* argv[]){
    double d, epsilon;
    int n;
    char *filename;
    int **row_ptr, **col_idx;
    double **val;
    filename = argv[1];
    d = atof(argv[2]);
    epsilon =  atof(argv[3]);
    n = atioi(argv[4]);
    read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val)
}