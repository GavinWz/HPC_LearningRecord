#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    MPI_Status status;
    int comm_sz, my_rank, sum, recv;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(my_rank != 0){
        recv = my_rank;
        MPI_Send(&recv, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }
    else{
        sum = 0;
        for(int source = 1; source < comm_sz; source++){
            MPI_Recv(&recv, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
            sum += recv;
            printf("Receive num %d.\n", recv);
        }
        printf("sum = %d\n", sum);
    }
    
  

    MPI_Finalize();
}