#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    MPI_Group group;
    int comm_sz, my_rank, group_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_group(MPI_COMM_WORLD, &group);
    MPI_Group_rank(group, &group_rank);
    printf("I'm rank %d in this group.\n", group_rank);

    MPI_Finalize();
}