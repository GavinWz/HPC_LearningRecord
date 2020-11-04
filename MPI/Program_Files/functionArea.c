#include<stdio.h>
#include<mpi.h>
#include<math.h>

double f(double num);
double Trap(double a, double b, int n, double h);

int main(int argc, char* argv[]){
    int a = 0, b = 32, n = 32;
    int comm_sz, my_rank;
    double total_integral, local_integral;

    double h = (b - a) / (double)n;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    printf("my_rank = %d, comm_sz = %d\n", my_rank, comm_sz);
    int local_n = n / comm_sz; //Suppose n is divisible by comm_sz
    double local_a = a + my_rank * local_n * h;
    double local_b = local_a + local_n * h;
    local_integral = Trap(local_a, local_b, local_n, h);

    /* way 1 */
    if(my_rank != 0){
        MPI_Send(&local_integral, 1, MPI_DOUBLE, 
            0, 0, MPI_COMM_WORLD);
    }
    else{
        total_integral = local_integral;
        double receive;
        for(int i = 1; i < comm_sz; i++){
            MPI_Recv(&local_integral, 1, MPI_DOUBLE, i, 0, 
                MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_integral += local_integral;
        }
        printf("%lf", total_integral);
    }

    /* way two */
    // MPI_Reduce(&local_integral, &total_integral, 1, MPI_DOUBLE, 
    //     MPI_SUM, 0, MPI_COMM_WORLD);
    // if(my_rank == 0)
    // printf("%lf", total_integral);

    MPI_Finalize();
    return 0;
}

double f(double num){
    return num;
}

double Trap(double a, double b, int n, double h){
    double area = 0;
    for(int i = 0; i <= n-1; i++){
        area += (f(a+i*h) + f(a+(i+1)*h)) / 2.0 * h;
    }
    return area;
}