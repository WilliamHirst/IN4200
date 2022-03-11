#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val) {
     FILE *fp;
     char line [256];
     fp = fopen(filename, "r");
     fscanf(fp,"%[^\n]",line);
 }
