#include<stdio.h>
#include<stdlib.h>

#define N 1000
#define M sizeof(double) * N

int main(){
    double *h_a = (double*)malloc(M);
    for(int i = N - 1; i >= 0; i--){
        h_a[i] = i;
        printf("a[%d] = %lf\n", i, h_a[i]);
    }
}