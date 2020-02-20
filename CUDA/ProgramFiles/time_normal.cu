#include<stdio.h>
#include<stdlib.h>
#include "error.cuh"

void addArrays(float *a, float *b, float *c, int N);

int main(){
    const int N = 100000;
    const int M = sizeof(float) * N;
    float *h_a, *h_b, *h_c;
    float value_a = 1.11, value_b = 2.22;
    int i;

    h_a = (float*)malloc(M);
    h_b = (float*)malloc(M);
    h_c = (float*)malloc(M);

    for(i = 0; i < N; i++)
        h_a[i] = value_a;
    for(i = 0; i < N; i++)
        h_b[i] = value_b;

    cudaEvent_t start, end;
    cudaEventCreate(&start);
    cudaEventCreate(&end);
    cudaEventRecord(start);
    cudaEventQuery(start);

    addArrays(h_a, h_b, h_c, N);

    cudaEventRecord(end);
    cudaEventSynchronize(end);

    float time_passed;
    cudaEventElapsedTime(&time_passed, start, end);
    printf("Time passed %f ms.\n", time_passed);
    
    cudaEventDestroy(start);
    cudaEventDestroy(end);

    free(h_a);
    free(h_b);
    free(h_c);
    return 0;
}

void addArrays(float *a, float *b, float *c, int N){
    for(int i = 0; i < N; i++){
        c[i] = a[i] + b[i];
    }
}