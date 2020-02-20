#include "error.cuh"
#include<stdio.h>
__global__ void myKernel(){
    printf("Hello World.\n");
}

int main(){
    myKernel<<<2, 2>>>();
    CHECK(cudaGetLastError());
    CHECK(cudaDeviceSynchronize());
    // cudaDeviceReset();
    return 0;
}