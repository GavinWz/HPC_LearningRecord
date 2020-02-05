#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    
    int comm_sz, my_rank, new_rank1, new_rank2, result_rank;
    MPI_Group group, new_group1, new_group2, result1, result2;

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_group(MPI_COMM_WORLD, &group);
    int members[10];
    int index = 0;
    for(int i = 0; i < comm_sz/2; i++){
        members[i] = i * 2 + 1;
    }
    
    /*new_group1:process{1,3,5,...}*/
    /*new_group2:process{2,4,6,...}*/
    /*result = new_group1 + new_group2 = {1,2,3,4,5,6,...}*/
    MPI_Group_incl(group, comm_sz/2, members, &new_group1);
    MPI_Group_excl(group, comm_sz/2, members, &new_group2);
    MPI_Group_union(new_group1, new_group2, &result1);

    MPI_Group_rank(new_group1, &new_rank1);
    MPI_Group_rank(new_group2, &new_rank2);
    MPI_Group_rank(result1, &result_rank);
    printf("Process %d in group1 is %d,\t in group2 is %d,\t in union of \
group1 and group2 is %d.\n", my_rank, new_rank1, new_rank2, result_rank);
    
    MPI_Group_difference(new_group1, new_group2, &result_rank);
    printf("Process %d in group1 is %d,\t in group2 is %d,\t in difference of \
group1 and group2 is %d.\n", my_rank, new_rank1, new_rank2, result_rank);

    MPI_Group_intersection(new_group1, new_group2, &result_rank);
    printf("Process %d in group1 is %d,\t in group2 is %d,\t in intersection of \
group1 and group2 is %d.\n", my_rank, new_rank1, new_rank2, result_rank);

}