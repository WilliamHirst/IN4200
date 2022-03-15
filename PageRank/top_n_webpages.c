
void swapD(double *a, double *b) {
    double t=*a; *a=*b; *b=t;
}
void swapI(int *a, int *b) {
    int t=*a; *a=*b; *b=t;
}

void top_n_webpages (int N, double *scores, int n){

    int *perm = malloc(N*sizeof(int));
    int indx_1, indx_2;
    size_t j;
    for (int i = 0; i < N; i++) perm[i] = i;
    //Sort array.
    int changed_odd = 0;
    int changed_even = 0;
    int N_2 = N/2;
    int r = N%2 - 1;
    #pragma omp parallel 
    {
        for (size_t i = 0; i < N; i++)
        {   
            //Odd
            #pragma omp for reduction(+:changed_odd)
            for (j = 0; j < N_2; j++)
            {
                indx_1 = 2*j;
                indx_2 = 2*j+1;
                if (scores[indx_1] < scores[indx_2]){
                    swapI(&perm[indx_1], &perm[indx_2] );
                    swapD(&scores[indx_1], &scores[indx_2] );
                    changed_odd = 1;
                }
            }  
            //Even
            #pragma omp for reduction(+:changed_even)
            for (j = 0; j < N_2 + r; j++)
            {
                indx_1 = 2*j+1;
                indx_2 = 2*j+2;
                if (scores[indx_1] < scores[indx_2]){
                    swapI(&perm[indx_1], &perm[indx_2] );
                    swapD(&scores[indx_1], &scores[indx_2] );
                    changed_odd = 1;
                }
            }
            if (!changed_odd && !changed_even) {
                break;
            }
            #pragma omp barrier
            #pragma omp single
            {
                changed_odd = changed_even = 0;
            }
        }
    }
    printf("-------------------------------\n");
    printf("---------Highest scores--------\n");
    printf("-------------------------------\n");

    for (size_t i = 0; i < n; i++)
    {
        printf(" %ld. -- score: %.3f -- index: %d\n", i+1, scores[i], perm[i]);
    }
    printf("\n");

    free(perm);
    free(scores);


    

}