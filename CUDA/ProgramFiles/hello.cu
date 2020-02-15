#include<stdio.h>
__global__ void myKernel(){
    printf("Hello World.\n");
}

int main(){
    myKernel<<<1, 2>>>();
    cudaDeviceSynchronize();
    // cudaDeviceReset();
    return 0;
}