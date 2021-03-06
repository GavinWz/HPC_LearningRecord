## MPI_Learning record

1. 程序的开始与结束

```c
int MPI_Init(int *argc, char **argv)
```
通过MPI_Init函数进入MPI环境并完成初始化工作，标志并行代码的开始, 前后两个参数为main函数的默认参数。
```c
int MPI_Finalize(void)
```
通过MPI_Finalize函数从MPI环境中推出，标志并行代码的结束，如果不是MPI程序的最后一句则运行结果不可知

2. 获取进程的数量：

```c
int MPI_Comm_size(MPI_Comm comm, int *rank)
```

通信子：一组可以相互发送消息的进程集合。通常由MPI_Init()在用户启动程序时， 定义由用户自动的所有进程组成的通信子， 缺省值为MPI_COMM_WORLD。这个参数是MPI通信操作函数中必不可少的参数，用户限定参加通信的进程的范围。

第一个参数是通信子， 第二个参数返回进程的个数

3. 获取进程id

```c
int MPI_Comm_rank(MPI_Comm comm, int *rank)`
```

获得当前进程在制定通信域中的编号，将自身与其他程序区分。  

第一个参数是通信子，第二个参数返回进程的编号。

4. 获取处理器

```c
int MPI_Get_processor_name(char *name, int *resultlen)
char *name;  #返回处理器名
int *resultlen;  #在name中返回结果的长度
```

5. 运行时间
```c
double MPI_Wtime(void) //计算运行时间
double MPI_Wtick(void) //查看时间的精度
```

6. 同步

```c
int MPI_Barrier(MPI_Comm comm)
```  

7. 消息传递


```c
double MPI_Wtick(void) //查看时间的精度
```

8. 消息传递

```c
int MPI_Send(void* msg_buf_p,//发送缓冲区的起始地址；
    int msg_size, //缓冲区大小；
    MPI_Datatype msg_type, //发送信息的数据类型
    int dest, //目标进程的id值;
    int tag, //消息标签;
    MPI_Comm communicator)//通信子
```

```c
int MPI_Recv(void* msg_buf_p, //缓冲区的起始地址；
    int buf_size, //缓冲区大小；
    MPI_Datatype msg_type, //发送信息的数据类型；
    int source, //目标进程的id值；
    int tag, //消息标签；
    MPI_Comm communicator， //通信子；
    MPI_Status *status_p)//status_p对象，包含实际接收到的消息的有关信息
```

```c
void* msg_buf_p ： 
int buf_size ： 
MPI_Datatype msg_type ： 
int dest ：
int tag ： 
MPI_Comm communicator ： 
MPI_Status *status_p ： 
```

9. 地址偏移量

MPI_ADDRESS: 获得一个位置在内存中的地址
```c
int MPI_Address(void *location, MPI_Aint *address)

void *location: 调用者的内存位置；
MPI_Aint *address: 位置的对应地址
```

10. 集合通信函数

涉及通信子中的所有进程的通信函数称为集合通信。
```c                                          
int MPI_Reduce(
    void* input_data_p,     //每个线程需要提供的计算数据
    void* output_data_p,    //返回计算结果
    int count,              //每个线程提供的数据量
    MPI_Datatype datatype,  //数据类型
    MPI_OP operator,        //归约操作符
    int dest_process,       //在指定线程中返回
    MPI_Comm comm);
```

在指定线程中对通信子中每个线程中的数据进行特定的计算(MPI_OP)，并在该线程中返回计算结果。

```c
int MPI_Allreduce(
    void* input_data_p,     //每个线程需要提供的计算数据
    void* output_data_p,    //返回计算结果
    int count,              //每个线程提供的数据量
    MPI_Datatype datatype,  //数据类型
    MPI_OP operator,        //归约操作符
    MPI_Comm comm);
```

与上面类似，除去dest_process参数。在通信子的所有线程中均返回结果。   
具体实现：在一个线程中计算出结果后，将结果发布给其他线程。

MPI_OP:
|运算符值|含义|—|运算符值|含义
|---|---|---|---|---|
|MPI_MAX|求最大值||MPI_LOR|逻辑或
|MPI_MIN|求最小值||MPI_BOR|按位或
|MPI_SUM|求累加和||MPI_LXOR|逻辑异或
|MPI_PROD|求累乘积||MPI_BXOR|按位异或
|MPI_LAND|逻辑与||MPI_MAXLOC|求最大值和最大值所在位置
|MPI_BAND|按位与||MPI_MINLOC|求最小值和最小值所在位置

11. 广播
```c
int MPI_Bcast(
    void* data_p,
    int count,
    MPI_Datatype datatype,
    int source_proc,
    MPI_Comm comm
);
```
进程号为cource_proc的进程将data_p所引用的内存内容发送给通信子comm中的所有进程

12. 散射

```c
int MPI_Scatter(
    void*           send_buf_p, //需要处理的整体数据
    int             send_count, //发送到每个进程的数据量
    MPI_Datatype    send_type,
    void*           recv_buf_p, //本地定义的数组或其他容器用来存储分得的数据
    int             recv_count, //每个进程分得的数据量
    MPI_Datatype    recv_type,
    int             src_proc,   //负责读取和分发数据的进程
    MPI_Comm        comm
);
```
若通信子comm包含comm_sz个进程，那么MPI_Scatter函数会将send_buf_p所引用的数据分成comm_sz份，第一份分给0号进程，第二分分给1号进程……以此类推。

13. 聚集

```c
int MPI_Gather(
    void*           send_buf_p,
    int             send_count,
    MPI_Datatype    send_type,
    void*           recv_buf_p,
    int             recv_count,
    MPI_Datatype    recv_type,
    int             dest_proc,
    MPI_Comm        comm
);
```
