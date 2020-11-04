#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

void Read_vector(
        double local_a[],
        int local_n,
        int n,  
        char vec_name[],
        int my_rank,
        MPI_Comm comm);

int main(){
    int comm_sz, my_rank;
    MPI_Init(NULL,NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    double* a;
    char* name;
    int n = 20;
    int local_n = n / comm_sz;
    Read_vector(a, local_n, n, name, my_rank, MPI_COMM_WORLD);
    MPI_Finalize();
}

void Read_vector(
        double local_a[],
        int local_n,
        int n,  
        char vec_name[],
        int my_rank,
        MPI_Comm comm){
    double *a = NULL;
    local_a = malloc(local_n*sizeof(double));
    int i;
    if(my_rank == 0){
        a = malloc(n*sizeof(double));
        for(i = 0; i < n; i++){
            a[i] = i + 1;
        }
        MPI_Scatter(a, local_n, MPI_DOUBLE, local_a, 
            local_n, MPI_DOUBLE, 0, comm);
        for(i = 0; i < local_n; i++)
            printf("%lf\n", local_a[i]);
        free(a);
    }
    else{
        MPI_Scatter(a, local_n, MPI_DOUBLE, local_a, 
            local_n, MPI_DOUBLE, 0, comm);
        for(i = 0; i < local_n; i++)
            printf("%lf\n", local_a[i]);
    }
    
}