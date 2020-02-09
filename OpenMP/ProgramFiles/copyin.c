#include<stdio.h>
#include<omp.h>

int g = 10;
#pragma omp threadprivate(g)

int main(){
    printf("Global g = %d\n", g);
    #pragma omp parallel for copyin(g)
    for(int i = 0; i < 4; i++){
        g += i;
        printf("thread %d, g = %d\n", omp_get_thread_num(), g);
    }
    printf("After parallel operate, Global g = %d\n", g);
    
}