#include<stdio.h>
#include<omp.h>

int main(){
    #pragma omp parallel num_threads(4)
    {
        printf("I'm thread %d of %d.\n", 
            omp_get_thread_num(), omp_get_num_threads());
        printf("Now, there are %d avalibal threads.\n", 
            omp_get_num_procs());
    
    }

}