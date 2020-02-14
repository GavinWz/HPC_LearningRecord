#include<stdio.h>

__global__ void multiThreads(){
    const int block = blockIdx.x;
    const int threadx = threadIdx.x;
    const int thready = threadIdx.y;
    printf("I come from block %d and thread(%d, %d).\n", block, threadx, thready);
}

int main(){
    dim3 block_size(2, 4);
    multiThreads<<<1, block_size>>>();
    return 0;
}