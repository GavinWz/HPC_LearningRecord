#include<stdio.h>
#include<omp.h>

omp_lock_t lock;

int main()
{
    int i, sum = 0;
    omp_init_lock(&lock);
    #pragma omp parallel for shared(sum)
    for(i = 0; i < 3; i++){
        omp_set_lock(&lock);
        sum += i;
        omp_unset_lock(&lock);
    }
    printf("With the lock, sum is always %d\n", sum);
    printf("If there is no lock here, the answer will be indeterminate.\n");

    printf("Test omp_test_lock(): \n");
    sum = 0;
    #pragma omp parallel for shared(sum)
    for(i = 0; i < 3; i++){
        if(omp_test_lock(&lock)){
            sum += i;
            omp_unset_lock(&lock);
        }
        else
            printf("Thread %d can't get lock.\n", omp_get_thread_num());
        
    }
    omp_destroy_lock(&lock);
    printf("With the test lock, sum = %d\n", sum);
}
