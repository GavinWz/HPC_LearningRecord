#include<stdio.h>
#include<mpi.h>
#include<math.h>

double f(double num);
double Trap(double a, double b, int n, double h);

int main(int argc, char* argv[]){
    int a = 0, b = 32, n = 32;
    int comm_sz, my_rank;
    double h = (b - a) / (double)n;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    // printf("my_rank = %d, comm_sz = %d\n", my_rank, comm_sz);
    int local_n = n / comm_sz;
    double local_a = a + my_rank * local_n * h;
    double local_b = local_a + local_n * h;
    
    // printf("%f, %f, %d， %f\n", local_a, local_b, local_n, h);
    double local_integral = Trap(local_a, local_b, local_n, h);
    // printf("%f\n", local_integral);
    if(my_rank != 0){
        MPI_Send(&local_integral, sizeof(local_integral), MPI_DOUBLE, 
            0, 1, MPI_COMM_WORLD);
    }
    else{
        double total_integral = local_integral;
        printf("1. %f,%f\n", local_integral, total_integral);
        for(int i = 1; i <= comm_sz; i++){
            MPI_Recv(&local_integral, 8, MPI_DOUBLE, MPI_ANY_SOURCE, 
                1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_integral = total_integral + local_integral;
            printf("3. %f,%f\n", local_integral, total_integral);
        }
        printf("%lf", total_integral);
    }
    // MPI_Finalized();
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