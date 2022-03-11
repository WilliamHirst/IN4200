#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 void read_graph_from_file(char *filename){ // int *n, int **row_ptr, int **col_idx, double **val){
    FILE *fp;
    int edges, N;
    char *line  = NULL;
    size_t size_line = 32;
    ssize_t reader;
    fp = fopen(filename, "r");
    
    for(int i = 0; i<4; i++){
        reader = getline(&line, &size_line, fp);
        if (i == 1) fscanf(fp, " %*s %*s %d %*s %d", &N, &edges);
    }
    printf("Number of nodes: %d --- Number of edges: %d\n", N, edges);
    int tot_edges [edges][2];

    int node_from, node_to, counter;
    counter = 0;
    while ((fscanf(fp,"%d %d", &tot_edges[counter][0], &tot_edges[counter][1])) != EOF) {
        counter += 1;
    }
    printf("Nodes and connections loaded.\n");

    fclose (fp);
   

 }
