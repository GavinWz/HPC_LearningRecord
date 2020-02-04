#include<stdio.h>
#include<mpi.h>

/*All the processors send a message to processor 0.*/

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    
    int comm_sz, my_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    char message[100];
    char messages[100][100];
    sprintf(message, "I'm process %d of %d", my_rank, comm_sz);
    MPI_Gather(message, sizeof(message), MPI_CHAR, messages, 
        sizeof(message), MPI_CHAR, 0, MPI_COMM_WORLD);
    
    if(my_rank == 0){
        for(int id = 0; id < comm_sz; id++){
            printf("%s\n", messages[id]);
        }
    }


    MPI_Finalize();
}