#include<iostream>
#include<mpi.h>

using namespace std;

int main(){
	int my_rank, size;
	MPI_Status status;
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	if(my_rank != 0){
		for(int i = 0; i < 100; i++)
			MPI_Send(&my_rank, 1, MPI_INT, 0, i, MPI_COMM_WORLD);
	}
	else{
		int gain;
		for(int i = 0; i < 100 * (size - 1); i++){
			MPI_Recv(&gain, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			cout << status.MPI_SOURCE << "  " << status.MPI_TAG << endl;
			/*MPI_Status是一个结构体，总共有五个成员变量，用户可直接访问其中的三个属性：
			 * typedef struct{
			 * ... ...
			 * int MPI_SOURCE;  //消息源地址
			 * int MPI_TAG;     //消息标签
			 * int MPI_ERROR    //错误码
			 * }
			 */
		}

	}
	MPI_Finalize();
}
