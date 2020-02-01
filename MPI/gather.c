#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

void Print_vector(
    double local_num[],
    int local_n,
    int n,
    int my_rank,
    MPI_Comm comm
);

int main(){
    int comm_sz, my_rank, n, local_n;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    n = 8;
    local_n = n / comm_sz;
    double *local_num;
    Print_vector(local_num, local_n, n, my_rank, MPI_COMM_WORLD);
    MPI_Finalize();
}

void Print_vector(
    double local_num[],
    int local_n,
    int n,
    int my_rank,
    MPI_Comm comm
){
    double* num = NULL;
    int i;
    local_num = malloc(local_n*sizeof(double));
    for(i = 0; i < local_n; i++)
        local_num[i] = i + 1;
    if(my_rank == 0){
        num = malloc(n * sizeof(double));
        MPI_Gather(local_num, local_n, MPI_DOUBLE, num,
            local_n, MPI_DOUBLE, 0, comm);
        for(i = 0; i < n; i++){
            printf("%lf\n", num[i]);
        }
    }
    else{
        MPI_Gather(local_num, local_n, MPI_DOUBLE, num,
            local_n, MPI_DOUBLE, 0, comm);
    }
}