#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    
    int comm_sz, my_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    char message[100];
    int nums[5];
    if(my_rank == 0){
        sprintf(message, "I'm processor %d.\n", my_rank);
        
        for(int i = 0; i < 5; i++)
            nums[i] = i;
        
    }
    MPI_Bcast(message, sizeof(message), MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(nums, 5, MPI_INT, 0, MPI_COMM_WORLD);
    if(my_rank != 0){
        printf("%s", message);
        for(int i = 0; i < 5; i++)
            printf("%d  ", nums[i]);
        
    }

    MPI_Finalize();
}