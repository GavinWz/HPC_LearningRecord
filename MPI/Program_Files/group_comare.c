#include<stdio.h>
#include<mpi.h>
void printResult(int result);
int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    
    int comm_sz, my_rank, result;
    MPI_Group group, new_group1, new_group2;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_group(MPI_COMM_WORLD, &group);
    int members[10];
    int index, i;
    
    if(my_rank == 0){
        index = 0;
        for(i = 0; i < comm_sz; i++){
            if(i % 2 == 1)
                members[index++] = i;
        }
        MPI_Group_incl(group, comm_sz/2, members, &new_group1);
        MPI_Group_compare(group, new_group1, &result);
        printResult(result);

        
        MPI_Comm_group(MPI_COMM_WORLD, &new_group2);
        MPI_Group_compare(group, new_group2, &result);
        printResult(result);


    }


}
void printResult(int result){
    if(result == MPI_IDENT)
        printf("Identical\n");
    else if(result == MPI_SIMILAR)
        printf("Similar\n");
    else if(result == MPI_UNEQUAL)
        printf("Unequal\n");
    else
        printf("Error\n");
}
