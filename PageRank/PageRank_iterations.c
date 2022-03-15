

void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, 
                         double d, double epsilon, double *scores) {

  
    int *L = malloc(N*sizeof(int));
    memset(L , 0, N*sizeof(int));
    int edges = row_ptr[N];
    int nr_dang = N;
    
    #pragma omp parallel for
    for (size_t i = 0; i < edges; i++)
    {
        L[col_idx[i]] = 1;
        
    }
    
    #pragma omp parallel for reduction(-:nr_dang)
    for (size_t i = 0; i < N; i++)
    {   
        nr_dang -= L[i];
    }
    printf("Nr of dangling webpages: %d\n", nr_dang);
    printf("- - - - - - - - - - - - - - - - - -\n");


    int *dang_indx = malloc(nr_dang*sizeof(int));
    int counter = 0;
    
    #pragma omp parallel
    {
    #pragma omp for
    for (size_t i = 0; i < N; i++){
        if(L[i] == 0) {
            #pragma omp critical
            {
            dang_indx[counter] = i;
            counter ++;
            }
        }
    }
    }
    free(L);
    double max_diff = epsilon*2;
    double current_max = 10;
    double cur_diff = 0.0;
    double W = 0;
    double *cur_score = malloc(N*sizeof(double));
    double *prev_score = malloc(N*sizeof(double)); 
    memcpy(prev_score, scores, N*sizeof(double));
    size_t j,i,k;
    for (k = 0; k < nr_dang; k++) W += prev_score[dang_indx[k]];
    counter = 0 ;
    int max_count = 1e6;

    printf("Calculating scores....\n");
    printf("- - - - - - - - - - - - - - - - - -\n");
    #pragma omp parallel 
    {
    while (max_diff > epsilon && counter < max_count)
    {
        
        #pragma omp for schedule(dynamic) reduction(max: current_max) private(i,j, cur_diff)
        for (i = 0; i < N; i++)
        {  
            
            cur_score[i] = (double)(1.- d + d*W)/N;
            for (j = row_ptr[i]; j < row_ptr[i+1]; j++)
            {
                cur_score[i] +=  d * val[j]*prev_score[col_idx[j]];
            }
            cur_diff =  fabs(cur_score[i]-prev_score[i]);
            if (cur_diff>current_max) current_max = cur_diff;
        }
        #pragma omp master
        { 
            W = 0.0;
            for (k = 0; k < nr_dang; k++) W += cur_score[dang_indx[k]]; 
            memcpy(prev_score, cur_score, N*sizeof(double));
            counter ++;
            max_diff = current_max;
            current_max = 0; 
        }
        #pragma omp barrier
    }
    }
    //exit(0);
    if (counter == max_count) printf("Threshold not reached after  %d iterations.\n", counter);
    else printf("Threshold (%.2e) reached after  %d iterations. \n", epsilon, counter);
    printf("- - - - - - - - - - - - - - - - - -\n");

    memcpy(scores, prev_score, N*sizeof(double));
 
    free(dang_indx);
    free(cur_score);
    free(prev_score);

}