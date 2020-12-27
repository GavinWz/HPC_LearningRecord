/*
    n核树形结构方式并行求和。例：
    1  2  3  4
    3     7
    10
*/


#include<stdio.h>
#include<mpi.h>
int divisor = 2; //判断当前进程是接收者还是发送者
int diff = 1; //用于确定当前进程的合作进程
int main(int argc, char** argv){
    int my_rank, size, partner, recv;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int my_value = my_rank + 1;
    while(divisor <= size){
        if(my_rank % divisor != 0){  //当前进程为发送方
            partner = my_rank - diff;  //计算发送方的合作进程
            MPI_Send(&my_value, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
        }
        else{  //当前进程为接收方
            partner = my_rank + diff;  //计算接收方的合作进程
            MPI_Recv(&recv, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            my_value = my_value + recv;
        }
        divisor *= 2;  //每次迭代后divisor和diff成倍增加
        diff *= 2;
    }
    
    if(my_rank == 0)
        printf("%d", my_value);
}