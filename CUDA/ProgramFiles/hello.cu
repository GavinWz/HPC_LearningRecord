#include<stdio.h>
__global__ void myKernel(){
    printf("Hello World.\n");
}

int main(){
    myKernel<<<1, 1>>>();
    cudaDeviceSynchronize();
    return 0;
}