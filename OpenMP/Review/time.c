#include<stdio.h>
#include<omp.h>

void run();
int main(){
    int repeat = 10;
    double begin = omp_get_wtime();
    #pragma omp parallel for num_threads(6)
    for(int i = 0; i < repeat; i++){
        run();
    }
    double end = omp_get_wtime();
    printf("It totally spend %lf s.\n", end - begin);
    printf("There are %d processes totally.", omp_get_num_procs());
}

void run(){
    double sum = 0;
    double begin = omp_get_wtime();
    for(int i = 0; i < 10000000; i++)
        sum++;
    double end = omp_get_wtime();
    printf("Every time spend %lf s.\n", end-begin);
}