#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

/*Create a num list, then hand them out to all the processors*/

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    
    int comm_sz, my_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int *nums;
    int local_nums[5];
    if(my_rank == 0){
        nums = (int *)malloc(comm_sz * 4 * sizeof(int));
        for(int i = 0; i < comm_sz*4; i++)
            nums[i] = i;
    }

    MPI_Scatter(nums, 4, MPI_INT, local_nums, 4, MPI_INT, 0, MPI_COMM_WORLD);
    if(my_rank != 0){
        printf("I'm processor %d, my nums are:\n", my_rank);
        for(int i = 0; i < 4; i++)
            printf("%d ", local_nums[i]);
        printf("\n");
    }

    MPI_Finalize();
}