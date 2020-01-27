#include<mpi.h>
#include<stdio.h>
int main(int argc, char **argv){
	MPI_Init(&argc, &argv);  //signal of begins
	printf("Hello World!\n");
	MPI_Finalize();  //signal of end
	return 0;
}
