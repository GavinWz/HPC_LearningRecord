#include<iostream>
#include<mpi.h>
#define maxn 12

using namespace std;

int main(){
    int i, j, size, rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int length = maxn / size;
    int xlocal[length+2][maxn];
    for(i = 1; i <= length; i++){
        for(j = 0; j < length; j++){
            xlocal[i][j] = rank;
        }
    }
    for(j = 0; j < length; j++){
        xlocal[0][j] = -1;
        xlocal[length+1][j] = -1;
    }


	if(rank > 0){  
    //除第0号进程，所有进程(rank号)都需要将自己的第一行发送给rank-1号进程的第rank/size+1行
		MPI_Send(xlocal[1], maxn, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
	}
	if(rank < size - 1){
    //除了rank/size-1号进程（最后一个进程），所有进程(rank号)都需要将自己的最后一行发送给rank+1号进程的第0行
		MPI_Send(xlocal[length], maxn, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
	}
	if(rank > 0){
    //除第0号进程，所有进程(rank号)都需要接受rank-1号进程的第rank/size行作为第0行
		MPI_Recv(xlocal[0], maxn, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
 	}
	if(rank < size - 1){
    //除最后一个进程，所有进程(rank号)都需要接受rank+1号进程的第0行作为第rank/size+1行
		MPI_Recv(xlocal[length+1], maxn, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

    int errcnt;  //记录每个节点的出错情况
    for(i = 1; i <= length; i++){
        for(j = 0; j < length; j++){
            if(xlocal[i][j] != rank)
                errcnt++;
        }
    }
    for(j = 0; j < length; j++){
        if(xlocal[0][j] != rank-1)
            errcnt++;
        if(xlocal[length+1][j] != rank + 1 && rank != size - 1)
            errcnt++;
    }

    int errtot;  //记录所有节点的出错情况
    MPI_Reduce(&errcnt, &errtot, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank == 0){
        if(errtot == 0)
            cout << "Every thing is OK." << endl;
        else
            cout << "There are " << errtot << "errors" << endl;
    }
}