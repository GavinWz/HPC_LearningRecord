1. 程序的开始与结束
``int MPI_Init(int *argc, char **argv)``
通过MPI_Init函数进入MPI环境并完成初始化工作，标志并行代码的开始
``int MPI_Finalize(void)``
通过MPI_Finalize函数从MPI环境中推出，标志并行代码的结束，如果不是MPI程序的最后一句则运行结果不可知

2. 获取进程的数量：

``int MPI_Comm_size(MPI_Comm comm, int *rank)``

通信子：一组可以相互发送消息的进程集合。通常由MPI_Init()在用户启动程序时， 定义由用户自动的所有进程组成的通信子， 缺省值为MPI_COMM_WORLD。这个参数是MPI通信操作函数中必不可少的参数，用户限定参加通信的进程的范围。

第一个参数是通信子， 第二个参数返回进程的个数

3. 获取进程id

``int MPI_Comm_rank(MPI_Comm comm, int *rank)``

获得当前进程在制定通信域中的编号，将自身与其他程序区分。  

第一个参数是通信子，第二个参数返回进程的编号。

4. 获取处理器

```
int MPI_Get_processor_name(char *name, int *resultlen)
char *name;  #返回处理器名
int *resultlen;  #在name中返回结果的长度
```

5. 运行时间

``double MPI_Wtime(void) //计算运行时间``

``double MPI_Wtick(void) //查看时间的精度``


