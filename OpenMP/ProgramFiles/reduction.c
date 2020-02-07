#include<stdio.h>
#include<omp.h>

int main(){
    int sum= 0;
    #pragma omp parallel for reduction(+: sum)
    for(int i = 0; i < 8; i++){
        sum = i;
    }
    printf("sum = %d", sum);
}