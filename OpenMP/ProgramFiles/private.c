#include<stdio.h>
#include<omp.h>

int main(){
    /*private*/
    int num = 20;
    #pragma omp parallel for private(num) num_threads(2)
    for(int i = 0; i < 2; i++){
        num += i;
        printf("num = %d\n", num);
    }
    
    printf("For private num, after parallel, num = %d.\n", num);

    /*firstprivate*/
    num = 20;
    #pragma omp parallel for firstprivate(num) num_threads(2)
    for(int i = 0; i < 2; i++){
        num += i;
        printf("num = %d\n", num);
    }
    printf("For first private num, after parallel, num = %d.\n", num);

    /*lastprivate*/
    num = 20;
    #pragma omp parallel for firstprivate(num), lastprivate(num) num_threads(2)
    for(int i = 0; i < 2; i++){
        num += i;
        printf("num = %d\n", num);
    }
    
    printf("For last private num, after parallel, num = %d.\n", num);
}
