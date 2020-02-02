#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

/*在源进程中打包发送一个数据包到进程1，进程1解包并打印出数据。*/
int main(int argc, char* argv[]){
    int comm_sz, my_rank;
    MPI_Status status;
    int i, j, position;
    int k[5];      //输出缓冲区
    int buf[100];  //输入缓冲区

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    position = 0;
    if(my_rank == 0){
        i = 1;
        j = 2;
        MPI_Pack(&i, 1, MPI_INT, buf, 100, 
            &position, MPI_COMM_WORLD);
        MPI_Pack(&j, 1, MPI_INT, buf, 100, 
            &position, MPI_COMM_WORLD);
        MPI_Send(buf, position, MPI_PACKED,
            1, 99, MPI_COMM_WORLD);
    }
    else{
        MPI_Recv(k, 2, MPI_INT, 0, 99,
            MPI_COMM_WORLD, &status);
        position  = 0;
        MPI_Unpack(k, 2, &position, &i, 
            1, MPI_INT, MPI_COMM_WORLD);
        MPI_Unpack(k, 2, &position, &j,
             1, MPI_INT, MPI_COMM_WORLD);
        printf("%d %d\n", i, j);
    }

}