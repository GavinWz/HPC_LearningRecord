#include<mpi.h>
#include<stdio.h>
#include<string.h>
int main(int argc, char **argv){
	const int MAX_STRING = 100;
	int comm;
	int my_rank;
	char greeting[MAX_STRING];

	MPI_Init(&argc, &argv);  //signal of begin
	MPI_Comm_size(MPI_COMM_WORLD, &comm);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	if(my_rank != 0){
		sprintf(greeting, "Greetings from process %d of %d!",
			my_rank, comm);
		MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}
	else{
		printf("Greeting from progress %d of %d!\n", my_rank, comm);
		for(int q = 1; q < comm; q++){
			MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 
				0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("%s\n", greeting);
		}
	}
	MPI_Finalize();  //signal of end
	return 0;
}
