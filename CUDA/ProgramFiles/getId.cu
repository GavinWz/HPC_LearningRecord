#include<stdio.h>

__global__ void printId(){
    int blockId = blockIdx.x;
    int threadId = threadIdx.x;
    printf("I come from block %d - thread %d.\n", blockId, threadId);
}

int main(){
    printId<<<2, 4>>>();
    return 0;
} 