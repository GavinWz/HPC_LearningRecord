#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    
    int comm_sz, my_rank, result, new_size;
    MPI_Comm new_comm;
    MPI_Group group;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_group(MPI_COMM_WORLD, &group);

    MPI_Comm_create(MPI_COMM_WORLD, group, &new_comm);

    if(my_rank == 0){
        MPI_Comm_size(new_comm, &new_size);
        printf("The new comm's size is %d.\n", new_size);
    }

    MPI_Finalize();
}