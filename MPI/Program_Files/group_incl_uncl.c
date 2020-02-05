#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    
    int comm_sz, my_rank, new_rank;
    MPI_Group group, new_group;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_group(MPI_COMM_WORLD, &group);
    int members[10];
    int index = 0;
    for(int i = 0; i < comm_sz; i++){
        if(i % 2 == 1)
            members[index++] = i;
    }
    MPI_Group_incl(group, comm_sz/2, members, &new_group);

    MPI_Group_rank(new_group, &new_rank);
    if(new_rank != MPI_UNDEFINED)
        printf("In the process %d, the rank in the new group is %d\n", 
            my_rank, new_rank);
    MPI_Finalize();
}