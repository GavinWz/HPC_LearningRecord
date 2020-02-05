#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    
    int comm_sz, my_rank, new_rank1, new_rank2;
    MPI_Group group, new_group1, new_group2;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_group(MPI_COMM_WORLD, &group);
    int members[10], new_ranks[10], ranks[10];
    int index = 0;
    for(int i = 0; i < comm_sz/2; i++){
        members[i] = i * 2 + 1;
    }
    
    MPI_Group_incl(group, comm_sz/2, members, &new_group1);
    for(int i = 0; i < comm_sz/2; i++){
        new_ranks[i] = i;
    }
    MPI_Group_translate_ranks(new_group1, comm_sz/2, new_ranks, group, ranks);
    if(my_rank < comm_sz/2)
        printf("In the new group process %d, the rank in the previous is %d\n", 
            my_rank, ranks[my_rank]);
    
}