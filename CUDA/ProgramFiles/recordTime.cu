#include<stdio.h>
#include<stdlib.h>
#include "error.cuh"

__global__ void addArrays(float *a, float *b, float *c, int N);

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

    float *d_a, *d_b, *d_c;
    cudaMalloc((void**)&d_a, M);
    cudaMalloc((void**)&d_b, M);
    cudaMalloc((void**)&d_c, M);
    cudaMemcpy(d_a, h_a, M, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, M, cudaMemcpyHostToDevice);

    int block_size = 64;
    int grid_size = (N + block_size - 1) / block_size;

    cudaEvent_t start, end;
    cudaEventCreate(&start);
    cudaEventCreate(&end);
    cudaEventRecord(start);
    cudaEventQuery(start);

    addArrays<<<grid_size, block_size>>>(d_a, d_b, d_c, N);
    cudaMemcpy(h_c, d_c, M, cudaMemcpyDeviceToHost);
    // for(i = 0; i < N;i++)
    //     printf("%f\n", h_c[i]);

    cudaEventRecord(end);
    cudaEventSynchronize(end);
    float time_passed;
    cudaEventElapsedTime(&time_passed, start, end);
    printf("Time passed %f ms.\n", time_passed);

}

__global__ void addArrays(float *a, float *b, float *c, int N){
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if(index < N)
        c[index] = a[index] + b[index];
}