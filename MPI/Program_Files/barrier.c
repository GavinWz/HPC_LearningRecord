#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){
    int sum_error;
    int sum_correct;
    MPI_Init(&argc, &argv);
    
    int comm_sz, my_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

//     if(my_rank == 0){
//         sum_error = sum_correct = 0;
//     }
//     else
//     {
//         while(my_rank == 0){}
//     }
    

//     sum_error += my_rank;
    
//     printf("I'm processor %d, error sum without \
// barrier = %d\n", my_rank, sum_error);

    MPI_Barrier(MPI_COMM_WORLD);
    sum_correct += my_rank;
    printf("I'm processor %d, correct sum is %d\n",
         my_rank, sum_correct);

    MPI_Finalize();
}

int sum(int pre_sum, int rank){
    return pre_sum, rank;
}