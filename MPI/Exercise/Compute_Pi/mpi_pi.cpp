#include<iostream>
#include<time.h>
#include<mpi.h>

using namespace std;

double f(double x){
    return 4 / (1 + x * x);
}

int main(){
    int rank, size;
    double h;
    long n = 99988;
    h = 1.0 / n;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    clock_t start = clock();
    int np = n / size * rank;
    double sum = 0;
    for(int i = np; i < np + n / size; i++){
        sum += h * f((i + 0.5) * h);
    }
    
    double pi;
    MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    clock_t end = clock();
    if(rank == 1)
    cout <<  end - start << "s" << endl;
    MPI_Finalize();
    return 0;
}