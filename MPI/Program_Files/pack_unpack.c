#include<stdio.h>
#include<mpi.h>

/*Send the name and name length of processor 0 to other precessors*/

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    
    int comm_sz, my_rank, name_len, position;
    char name[MPI_MAX_PROCESSOR_NAME];
    char input_buf[100], output_buf[100];

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    
    if(my_rank == 0){
        MPI_Get_processor_name(name, &name_len);
        position = 0;
        MPI_Pack(&name_len, 1, MPI_INT, input_buf,
            100, &position, MPI_COMM_WORLD);
        MPI_Pack(name, name_len, MPI_CHAR, input_buf,
            100, &position, MPI_COMM_WORLD);
        for(int target = 1; target < comm_sz; target++)
            MPI_Send(input_buf, name_len+sizeof(int), MPI_CHAR, target, 1, MPI_COMM_WORLD);
    }
    else{
        position = 0;
        MPI_Status status;
        MPI_Recv(output_buf, 100, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
        MPI_Unpack(output_buf, 100, &position, &name_len, 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Unpack(output_buf, 100, &position, name, name_len, MPI_CHAR, MPI_COMM_WORLD);
        
        printf("%s\n", name);
        printf("%d\n", name_len);
    }
    MPI_Finalize();
}