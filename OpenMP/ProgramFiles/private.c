#include<stdio.h>
#include<omp.h>

int main(){
    int num = 20;
    #pragma omp parallel private(num) num_threads(2)
    {
        if(omp_get_thread_num() == 0){
            if(num == 20)
                printf("in private, num hasn't changed.\n");
            else{
                printf("in private num hasn's initialized.\n");
                num = 0;
            }
        }
        #pragma omp parallel for
        for(int i = 0; i < 2; i++){
            num += i;
            printf("num = %d\n", num);
        }
    }
    printf("For private num, after parallel, num = %d.\n", num);

    num = 20;
    #pragma omp parallel firstprivate(num) num_threads(2)
    {
        if(omp_get_thread_num() == 0){
            if(num == 20)
                printf("in firstprivatem, num hasn't changed.\n");
            else{
                printf("in firstprivatem, num hasn's initialized.\n");
                num = 0;
            }
        }
        #pragma omp parallel for
        for(int i = 0; i < 2; i++){
            num += i;
            printf("num = %d\n", num);
        }
    }
    printf("For first private num, after parallel, num = %d.\n", num);
}