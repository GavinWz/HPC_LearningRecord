#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    
    int comm_sz, my_rank, new_rank1, new_rank2;
    MPI_Group group, new_group1, new_group2;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_group(MPI_COMM_WORLD, &group);
    int members[10];
    int index = 0;
    for(int i = 0; i < comm_sz; i++){
        if(i % 2 == 1)
            members[index++] = i;
    }
    
    /*Odd*/
    MPI_Group_incl(group, comm_sz/2, members, &new_group1);
    MPI_Group_rank(new_group1, &new_rank1);
    if(new_rank1 != MPI_UNDEFINED)
        printf("In the process %d, the rank in the new group1 is %d\n", 
            my_rank, new_rank1);

    /*Plural*/
    MPI_Group_excl(group, comm_sz/2, members, &new_group2);
    MPI_Group_rank(new_group2, &new_rank2);
    if(new_rank2 != MPI_UNDEFINED)
        printf("In the process %d, the rank in the new group2 is %d\n", 
            my_rank, new_rank2);
    MPI_Finalize();
}