#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<math.h>

void sum();

int main(){
    int i;
    double start = omp_get_wtime();

    // clock_t start = clock();
    for(i = 0; i < 2; i++)
        sum();
    double end = omp_get_wtime();
    // clock_t end = clock();
    printf("Running 2 times spent without parallel: %lf\n", end - start);

    // start = clock();
    start = omp_get_wtime();
    #pragma omp parallel for
    for(i = 0; i < 2; i++)
        sum();
    // end = clock();
    end = omp_get_wtime();
    printf("Running 2 times spent  with   parallel: %lf\n", end - start);

}

void sum(){
    double sum = 0;
    // clock_t start = clock();
    double start = omp_get_wtime();
    for(int i = 0; i < 10000000; i++){
        sum++;

    }
    // clock_t end = clock();
    double end = omp_get_wtime();
    printf("Every time spend: %lf\n", end - start);

}