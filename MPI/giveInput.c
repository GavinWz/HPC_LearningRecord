#include<stdio.h>
#include<mpi.h>

void Get_input(
            int my_rank,
            int comm_sz,
            double* a_p,
            double* b_p,
            int* n_p){
        if(my_rank == 0){
            for(int dest = 1; dest < comm_sz; dest++){
                scanf("%lf%lf%d", a_p, b_p, n_p);
                MPI_Send(a_p, 1, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
                MPI_Send(b_p, 1, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
                MPI_Send(n_p, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
            }
        }
        else{
            MPI_Recv(a_p, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(b_p, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(n_p, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
int main(){
    int comm_sz, my_rank, n;
    double a, b;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    printf("I'm rank %d of %d.\n", my_rank, comm_sz);
    Get_input(my_rank, comm_sz, &a, &b, &n);
    if(my_rank != 0)
        printf("I'm rank %d of %d.\na = %lf, b = %lf, n = %d\n", my_rank, comm_sz, a, b, n);

}

