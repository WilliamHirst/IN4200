

void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, 
                         double d, double epsilon, double *scores) {

    int *L = malloc(N*sizeof(int));
    int edges = row_ptr[N];
    int nr_dang = N;

    for (size_t i = 0; i < edges; i++)
    {
        L[col_idx[i]] = 1;
    }
    
    for (size_t i = 0; i < edges; i++)
    {
        nr_dang -= L[i];
    }
    printf("Nr of dangling webpages: %d\n ", nr_dang);

    int *dang_indx = malloc(nr_dang*sizeof(int));
    int counter = 0;
    for (size_t i = 0; i < N; i++){
        if(L[i] == 0) {
            dang_indx[counter] = i;
            counter ++;
        }
    }
    printf("[");
    for (size_t i = 0; i < nr_dang; i++) printf("i = %d, ", dang_indx[i]);
    printf("]\n");


    double max_diff = epsilon*0.5;
    double cur_diff = 0;
    double W = 0;
    int *cur_score = malloc(N*sizeof(int));
    int *prev_score = malloc(N*sizeof(int)); 
    counter = 0 ;
    
    while (max_diff < epsilon && counter < 1)
    {
        for (size_t i = 0; i < N; i++)
        {  
            cur_score[i] = 0;
            for (size_t j = row_ptr[i]; i < row_ptr[i+1]; i++)
            {
                cur_score[i] += (double)(1.-d+d*W)/N + d * val[j]*prev_score[j];
            }
            cur_diff =  abs(cur_score[i]-prev_score[i]);

            if (cur_diff>max_diff) max_diff = cur_diff;
        }
        W = 0;
        for (size_t k = 0; k < nr_dang; k++) W += cur_score[dang_indx[k]]; 
        
        memcpy(prev_score, cur_score, N*sizeof(double));
        
        printf("[");
        for (size_t i = 0; i < N; i++)
        {
            printf("%d, ", cur_score[i]);
        }
        printf("]\n");
        counter ++;
        
    }


    

        
}