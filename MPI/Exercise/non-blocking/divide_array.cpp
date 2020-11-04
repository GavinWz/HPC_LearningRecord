#include<iostream>
#include<mpi.h>

using namespace std;

int main(){
	double x[maxn][maxn];
	int size, rank;
	MPI_Init(NULL,NULL);
	MPI_Comm_size(&size, MPI_COMM_WORLD);
	MPI_Comm_rank(&rank, MPI_COMM_WORLD);

	double xlocal[maxn][maxn / size];
	
}
