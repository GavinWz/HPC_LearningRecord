#include<stdio.h>
#include<omp.h>

int main()
{
    printf("There are %d available threads.\n", omp_get_num_procs());
}
