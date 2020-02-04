#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){

    char name[MPI_MAX_PROCESSOR_NAME];
    int length;

    MPI_Init(&argc, &argv);
    
    MPI_Get_processor_name(name, &length);
    printf("I'm %s\n", name);

    MPI_Finalize();
}