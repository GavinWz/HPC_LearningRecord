#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    MPI_Group group;
    int comm_sz, my_rank;
    MPI_Comm new_comm;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int caculate, color, key, new_rank;
    caculate = 3;
    color = my_rank % 3;
    key = my_rank / 3;
    MPI_Comm_split(MPI_COMM_WORLD, color, key, &new_comm);
    
    MPI_Comm_rank(new_comm, &new_rank);
    printf("world_rank is %d, new_rank is %d.\n", my_rank, new_rank);
    MPI_Finalize();
}