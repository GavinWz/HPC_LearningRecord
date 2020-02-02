#include<stdio.h>
#include<mpi.h>
#define SIZE 3
int main(){
    double a = 4, b = 8;
    int n = 16;
    int my_rank;
    double* recv;
    MPI_Init(NULL, NULL);
    /*prepare for array_of_blocklengths[]*/
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int array_of_blocklengths[SIZE] = {1,1,1};

    /*prepare for array_of_displacements[]*/
    MPI_Aint a_addr, b_addr, n_addr;
    MPI_Aint array_of_displacements[SIZE];
    MPI_Get_address(&a, &a_addr);
    array_of_displacements[0] = 0;
    MPI_Get_address(&b, &b_addr);
    array_of_displacements[1] = b_addr-a_addr;
    MPI_Get_address(&n, &n_addr);
    array_of_displacements[2] = n_addr-a_addr;

    /*prepare for array_of_types[]*/
    MPI_Datatype array_of_types[SIZE] = {MPI_DOUBLE,
        MPI_DOUBLE, MPI_INT};
    
    MPI_Datatype input_mpi_t_p;
    MPI_Type_create_struct(3, array_of_blocklengths,
        array_of_displacements, array_of_types, &input_mpi_t_p);
    MPI_Type_commit(&input_mpi_t_p);
    if(my_rank == 0){
        // MPI_Bcast(&recv, 1, input_mpi_t_p, 0, MPI_COMM_WORLD);
        MPI_Send(&a, 1, input_mpi_t_p, 0, 0, MPI_COMM_WORLD);
    }
    else
        MPI_Recv(recv, 1, input_mpi_t_p, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("%lf\n", recv[0]);
    MPI_Finalize();
    
    
}