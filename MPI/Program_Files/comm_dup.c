#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    
    int comm_sz, my_rank, result;
    MPI_Comm new_comm;

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_dup(MPI_COMM_WORLD, &new_comm);

    MPI_Comm_compare(MPI_COMM_WORLD, new_comm, &result);

    if(my_rank == 0) {
		if ( result == MPI_IDENT) 
			printf("The comms are identical.\n");
		else if ( result == MPI_CONGRUENT ) 
			printf("The comms are congruent.\n");
		else if ( result == MPI_SIMILAR ) 
			printf("The comms are similar.\n");
		else if ( result == MPI_UNEQUAL ) 
			printf("The comms are unequal.\n");
	}

    MPI_Finalize();
}