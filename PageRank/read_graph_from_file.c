#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
    {
        int t=*a; *a=*b; *b=t;
    }
void sort(int **arr, int beg, int end)
    {
    if (end > beg + 1) {
        int piv = arr[beg][1], l = beg + 1, r = end;
        while (l < r) {
            if (arr[l][1] <= piv)
                l++;
            else
                swap(&arr[l], &arr[--r]);
            
            }
    swap(&arr[--l], &arr[beg]);
    sort(arr, beg, l);
    sort(arr, r, end);
    }
}
void creat_CRS(int **arr, int *row_ptr, int *col_idx, double *val, int edges, int nr_links[]){
    int prev_row, row_index, col_index, row;
    prev_row = arr[0][1];
    row = 0;
    col_idx[0] = arr[0][0];
    val[0] = (double) 1. /nr_links[col_idx[0]];
    row_ptr[0] = 0;
    for(int i = 1; i < edges; i++){
        row_index = arr[i][1];
        col_index = arr[i][0];
        col_idx[i] = col_index;
        val[col_index] = (double) 1. /nr_links[col_index];
        if (prev_row != row_index){
            row_ptr[row] = i;
            row++;
        }
        prev_row = row_index;
        
    }
}

 void read_graph_from_file(char *filename, int **row_ptr, int **col_idx, double **val){
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

    row_ptr = malloc(edges * sizeof(int*));
    col_idx = malloc(edges * sizeof(int*));
    val = malloc(edges * sizeof(double*));

    (*col_idx) = malloc(edges*sizeof(int));
    (*row_ptr) = malloc((N+1)*sizeof(int));
    (*val) = malloc(edges*sizeof(double));


    int **tot_edges = malloc(edges * sizeof(int*));
    for(int i = 0; i<edges; i++) tot_edges[i] = malloc(2 * sizeof(int));


    int node_from, node_to, counter;
    counter = 0;
    int nr_links[N]; 
    while ((fscanf(fp,"%d %d", &tot_edges[counter][0], &tot_edges[counter][1])) != EOF) {
        nr_links[tot_edges[counter][0]] ++;
        counter += 1;
    }
    printf("Nodes and connections loaded.\n");
    fclose (fp);

    sort(tot_edges, 0 , edges);
    //for(int i = 0; i<edges; i++)
    //printf("%d %d \n",tot_edges[i][0], tot_edges[i][1]);

    creat_CRS(tot_edges, (*row_ptr), (*col_idx), (*val), edges, nr_links);
    for(int i = 0; i < edges; i++){
        printf("%f \n", (*val)[i]);
    }

 }

