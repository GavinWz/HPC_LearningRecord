#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

double* exchange(double nums[][2], int x, int y){
    double *num  = (double*)malloc(x*y*sizeof(double));
    int i = 0, index = 0;
    for(; i < x; i++){
        for(int j = 0; j < y; j++){
            num[index] = nums[i][j];
            index++;
        }
    }
    return num;
}

void Mat_vect_mult(
    double local_a[],
    double local_x[],
    double local_y[],
    int local_m,
    int n,
    int local_n,
    MPI_Comm comm
){
    double *x;
    int local_i, j;
    x = malloc(local_n*sizeof(double));
    MPI_Allgather(local_x, local_n, MPI_DOUBLE, x, 
            local_n, MPI_DOUBLE, comm);
    for(local_i = 0; local_i < local_m; local_i++){
        local_y[local_i] = 0.0;
        for(j = 0; j < n; j++){
            local_y[local_i] += local_a[local_i*n+j] * x[j];
        }
    }
}

int main(){
    int comm_sz, my_rank, n, local_n;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    n = 8;
    int local_a[10];
    local_n = n / comm_sz;

    double nums[3][2] = {{1,2},{3,4},{5,6}};
    double *a = (double*)malloc(10*sizeof(double));
    a = exchange(nums, 3, 2);
    double x[2] = {1, 2};
    double *y = (double*)malloc(10*sizeof(double));

    Mat_vect_mult(a, x, y, 3, 2, 2, MPI_COMM_WORLD);

    for(int i = 0; i < 3; i++)
        printf("%lf\n", y[i]);
    
    if(my_rank == 0){
        double* local_y = (double*)malloc(6*sizeof(double));
        MPI_Gather(y, local_n, MPI_DOUBLE, local_y, local_n,
            MPI_DOUBLE, 0, MPI_COMM_WORLD);
        double sum = 0;
        for(int i = 0; i < local_n; i++){
            sum += local_y[i];
        }
        printf("answer = %lf\n", sum);
    }
}