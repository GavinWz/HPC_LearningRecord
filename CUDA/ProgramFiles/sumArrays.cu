#include<stdio.h>

__global__ void sumKernel(double *d_a, double *d_b, double *d_c, int n);

double *h_a, *h_b, *h_c;
const int N = 1000;
const int M = sizeof(double) * N;

int main(){
    h_a = (double*)malloc(M);
    h_b = (double*)malloc(M);
    h_c = (double*)malloc(M);
    
    for(int i = N - 1; i >= 0; i--)
        h_a[i] = i;
    for(int i = 0; i < N; i++)
        h_b[i] = i;

    double *d_a, *d_b, *d_c;
    cudaMalloc((void**)&d_a, M);
    cudaMalloc((void**)&d_b, M);
    cudaMalloc((void**)&d_c, M);
    cudaMemcpy(d_a, h_a, M, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, M, cudaMemcpyHostToDevice);

    const int block_size = 64;
    const int grid_size = N / block_size + 1;
    sumKernel<<<grid_size, block_size>>>(d_a, d_b, d_c, N);

    cudaMemcpy(h_c, d_c, M, cudaMemcpyDeviceToHost);
    for(int i = 0; i < N; i++)
        printf("%lf + %lf = %lf\n",h_a[i], h_b[i], h_c[i]);

    free(h_a);
    free(h_b);
    free(h_c);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
__global__ void sumKernel(double *d_a, double *d_b, double *d_c, int n){
    int index = blockDim.x * blockIdx.x + threadIdx.x;
    d_c[index] = d_a[index] + d_b[index];
}