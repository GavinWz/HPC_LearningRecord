# 非阻塞通信(Non-block Communication)

[非阻塞通信](https://www3.nd.edu/~zxu2/acms60212-40212-S12/Lec-04.pdf)

## 优点
* 允许在通信的初始化和完成之间进行分离。
* 可以避免死锁

## 缺点
* 开发、维护和代码调试过程较为复杂

## MPI Non-block Send/Recv

### Syntax

```c
int MPI_Isend(
	void* message,	/*in*/
	int count,		/*in*/
	MPI_Datatype datatype,	/*in*/
	int dest,		/*in*/
	int tag,		/*in*/
	MPI_Comm comm,	/*in*/
	MPI_Request* request	/*out*/
)

int MPI_Irecv(
	void* message,	/*out*/
	int count,		/*in*/
	MPI_Datatype datatype,	/*in*/
	int source,		/*in*/
	int tag,		/*in*/
	MPI_Comm comm,	/*in*/
	MPI_Request* request	/*out*/
)
```

### 细节

* 非阻塞通信至少需要两个函数调用：一个调用启动操作，一个调用完成操作
* ``request``用来查询通信子的状态或者等待通信子的完成
* 用户不可以在数据传送结束之前修改发送缓冲区
* 用户不能在数据接收结束之前使用接收缓冲区

### 非阻塞通信发送/接收的结束

* 发送结束，意味着发送方可自由更新发送缓冲区的信息
* 接收结束，意味着接收方的接收缓冲区包含了要接收的数据

```c
int MPI_Wait(
	MPI_Request* request, 	/*in-out*/
	MPI_Status* status		/*out*/
)

int MPI_Test(
	MPI_Request* request, 	/*out*/
	int* flag, 				/*out*/
	MPI_Status* status		/*out*/
)	
```

* ``request``用来识别之前的发送与接收
* MPI_Wait() 在所有操作完成时返回，并更新接收状态
* MPI_Test() 立即返回，若相应的request处理完成，则``flag = true``