#include<stdio.h>
#include<mpi.h>

/*使用函数MPI_Wtime计算并行代码的运行时间，并且在
两次计算时间的函数之间用函数MPI_WTICK打印出精度。*/

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);

    double start, finish;

    start = MPI_Wtime();
    printf("The precision is %lf", MPI_Wtick());
    finish = MPI_Wtime();

    printf("Running %lf seconds.\n", finish - start);
    MPI_Finalize();
}