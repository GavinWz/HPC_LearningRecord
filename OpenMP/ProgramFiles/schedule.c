#include<stdio.h>
#include<omp.h>

int main(){
    printf("static\n");
    #pragma omp parallel for schedule(static, 2)
    for(int i = 0; i < 16; i++)
        printf("thread %d, i = %d\n", omp_get_thread_num(), i);

    printf("\ndynamic\n");
    #pragma omp parallel for schedule(dynamic, 2)
    for(int i = 0; i < 16; i++)
        printf("thread %d, i = %d\n", omp_get_thread_num(), i);

    printf("\nguided\n");
    #pragma omp parallel for schedule(guided, 2)
    for(int i = 0; i < 16; i++)
        printf("thread %d, i = %d\n", omp_get_thread_num(), i);

    
}