
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
    for (size_t i = 0; i < N; i++)
    {   
        //Odd
        if(i % 2 != 0){
            for (j = 0; j < N/2; j++)
            {
                indx_1 = 2*j+1;
                indx_2 = 2*j+2;
                if (scores[indx_1] < scores[indx_2]){
                    swapI(&perm[indx_1], &perm[indx_2] );
                    swapD(&scores[indx_1], &scores[indx_2] );
                }
            } 
            
        }
        //Even
        else{
            for (j = 0; j < N/2; j++)
            {
                indx_1 = 2*j;
                indx_2 = 2*j+1;
                if (scores[indx_1] < scores[indx_2]){
                    swapI(&perm[indx_1], &perm[indx_2] );
                    swapD(&scores[indx_1], &scores[indx_2] );
                }
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