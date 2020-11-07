#include<iostream>
#include<mpi.h>

#define maxn 12
using namespace std;

int main(){
    int rank, size, i, j;
    MPI_Status status, status1, status2, status3;
    MPI_Request request, request1, request2, request3;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int n_row = maxn / size;
    double xlocal[n_row+2][maxn];

    for(i = 1; i <= n_row; i++){
        for(j = 0; j < n_row; j++){
            xlocal[i][j] = rank;
        }
    }
    for(j = 0; j < n_row; j++){
        xlocal[0][j] = -1;
        xlocal[n_row+1][j] = -1;
    }

    if(rank > 0){
        MPI_Isend(xlocal[1], maxn, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
    }
    if(rank < size - 1){
        MPI_Isend(xlocal[n_row], maxn, MPI_DOUBLE, rank + 1, 2, MPI_COMM_WORLD, &request1);
        MPI_Wait(&request1, &status1);
    }
    if(rank > 0){
        MPI_Irecv(xlocal[0], maxn, MPI_DOUBLE, rank - 1, 2, MPI_COMM_WORLD, &request2);
        MPI_Wait(&request2, &status2);
    }
    if(rank < size - 1){
        MPI_Irecv(xlocal[n_row+1], maxn, MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD, &request3);
        MPI_Wait(&request3, &status3);
    }

    int errnum = 0;
    for(i = 1; i <= n_row; i++){
        for(j = 0; j < n_row; j++){
            if(xlocal[i][j] != rank)
                errnum++;
        }
    }
    for(j = 0; j < n_row; j++){
        if(xlocal[0][j] != rank - 1)
            errnum++;
        if(xlocal[n_row+1][j] != rank + 1 && rank != size - 1)
            errnum++;
    }
    int totnum;
    MPI_Reduce(&errnum, &totnum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank == 0)
        cout << totnum << endl;
}