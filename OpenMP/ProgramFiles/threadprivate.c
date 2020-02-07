#include<stdio.h>
#include<omp.h>

int num = 0;
#pragma omp threadprivate(num)
int main(int argc, char* argv[]){
    

    #pragma omp parallel
    {
        num = omp_get_thread_num();
    }

    #pragma omp parallel
    {
       printf("For thread %d, num = %d.\n",omp_get_thread_num(), num); 
    }
    return 0;
}
    

