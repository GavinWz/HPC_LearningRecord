#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    
    int comm_sz, my_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    printf("I'm process %d of %d", my_rank, comm_sz);

    MPI_Finalize();
}