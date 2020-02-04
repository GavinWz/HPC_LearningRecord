#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    
    int comm_sz, my_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int a = 5, b = 4, n = 9;
    double c = 9;
    MPI_Aint adrs_a, adrs_b, adrs_c;
    MPI_Address(&a, &adrs_a);
    MPI_Address(&b, &adrs_b);
    MPI_Address(&c, &adrs_c);

    int dists1, dists2;
    dists1 = adrs_b - adrs_a;
    dists2 = adrs_c - adrs_b;

    if(my_rank == 0){
        printf("The distance between a and b is %d\n", dists1);
        printf("The distance between b and c is %d\n", dists2);
        
    }
    MPI_Finalize();
}