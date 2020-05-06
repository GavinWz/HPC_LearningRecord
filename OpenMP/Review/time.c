#include<stdio.h>
#include<omp.h>

void run();
int main(){
    int test = 10;
    double begin = omp_get_wtime();
    #pragma omp parallel sections firstprivate(begin) shared(test)
    {
        #pragma omp section
        {
            double end = omp_get_wtime();
            test += 5;
            printf("1. %lf  %d\n", end - begin, test);
        }
        #pragma omp section
        {
            double end = omp_get_wtime();
            test += 15;
            printf("2. %lf  %d\n", end - begin, test);
        }
    }
    double end = omp_get_wtime();
    printf("   %lf  %d\n", end - begin, test);
}

void run(){
    double sum = 0;
    double begin = omp_get_wtime();
    for(int i = 0; i < 10000000; i++)
        sum++;
    double end = omp_get_wtime();
    printf("Every time spend %lf s.\n", end-begin);
}