## MPI_Learning_Record


环境下载:  
http://www.mpich.org/downloads/

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

参数: 第一个参数是通信子， 第二个参数返回进程的个数

3. 获取进程id

```c
int MPI_Comm_rank(MPI_Comm comm, int *rank)
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
double MPI_Wtime(void) //获取时间
double MPI_Wtick(void) //查看时间的精度
```

6. 同步

```c
int MPI_Barrier(MPI_Comm comm)
```  

7. 时间精度


```c
double MPI_Wtick(void) //查看时间的精度
```

8. 消息传递

```c
int MPI_Send(void* msg_buf_p,//发送缓冲区的起始地址；
    int msg_size, //缓冲区大小
    MPI_Datatype msg_type, //发送信息的数据类型
    int dest, //目标进程的id值
    int tag, //消息标签
    MPI_Comm communicator//通信子
);
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

10. (规约)集合通信函数

涉及通信子中的所有进程的通信函数称为集合通信。
```c                                          
int MPI_Reduce(
    void* input_data_p,     //每个线程需要提供的计算数据
    void* output_data_p,    //返回计算结果
    int count,              //每个线程提供的数据量
    MPI_Datatype datatype,  //数据类型
    MPI_OP operator,        //归约操作符
    int dest_process,       //在指定线程中返回
    MPI_Comm comm
);
```

在指定线程中对通信子中每个线程中的数据进行特定的计算(MPI_OP)，并在该线程中返回计算结果。

```c
int MPI_Allreduce(
    void* input_data_p,     //每个线程需要提供的计算数据
    void* output_data_p,    //返回计算结果
    int count,              //每个线程提供的数据量
    MPI_Datatype datatype,  //数据类型
    MPI_OP operator,        //归约操作符
    MPI_Comm comm
);
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
在指定线程dest_proc中收集当前线程传来的数据，保存在大小为recv_count的recv_type类型数组recv_count中

14. 派生数据类型 ???

一个派生数据类型是由一系列的MPI基本数据类型和每个数据类型的偏移所组成的

假设一个进程里变量a,b,n和它们在内存中的位置如下
变量|地址
--|--
a|24
b|40
n|48
则可以用以下的派生数据类型表示这些数据项：

{(MPI_DOUBLE,0),(MPI_DOUBLE,16),(MPI_INT,24)}

每组数据的第二个元素是该数据项相对于起始位置的偏移, 即为当前数据与起始数据的内存地址差值。

可以用MPI_Type_creaate_struct函数创建有不同基本数据类型的元素组成的派生数据类型。

```c
int MPI_Type_create_struct(
    int count, //数据类型中元素的个数
    int array_of_blocklengths[]， //允许单独的数据项可以是个数组,每个元素表示数组长度
    MPI_Aint array_of_displacements[]，//距离消息起始位置的偏移量,单位为字节
    MPI_Datatype array_of_types[],//数据类型
    MPI_Datatype* new_type_p  //函数建立的新的数据类型
);
```
可以使用MPI_Get_address函数来找到制定元素的内存地址
```c
int MPI_Get_address(
    voiod* location_p,
    MPI_Aint* adddress_p
);
```
MPI_Aint是个长整数型, address_p返回location_p所指向的内存单元的地址

生成新的数据类型之后需要调用函数MPI_Type_commit去指定它:
```c
int MPI_Type_commit(MPI_Datatype* new_mpi_t_p);
```

调用派生数据类型: 以MPI_Bcast测试:
```c
MPI_Bcast(&a, 1, input_mpi_t, 0, comm);
```

15. 数据的打包(Pack)

将不连续的数据或是不相同的数据类型的数据一起发送到其它进程

```c
int MPI_Pack(
    void* inbuf,  //待打包的数据
    int incount,  //打包的数据量
    MPI_Datatype datatype, //数据项的类型
    void *outbuf,  //输入冲区地址
    int outcount,  //输入缓冲区大小
    int *position, //缓冲区第一个用于打包的位置
    MPI_Comm, comm //通信子
);

int MPI_Unpack(
    void* inbuf,             // 指向待解包缓冲区的指针
    int insize,              // 缓冲区大小（单位为 Byte）
    int* position,           // 输出缓冲区中第一个用于打包的位置（地址偏移量）
    void* outbuf,            // 指向解包后数据的指针 
    int outcount,            // 解包元素个数    
    MPI_Datatype datatype,   // 数据类型
    MPI_Comm comm            // 通信子
 );
```

缓冲区的类型任意, 意在分配指定大小的空间足够打包解包时使用, position大小随打包和解包增加和减少

打包完成后可以通过MPI_Send等发送数据的函数将输入缓冲区**outbuf**发送到其他线程,类型为**MPI_PACKED**

接收函数MPI_Recv等接收到其他线程发来的包后,需要对其进行解包操作,提取出相应的数据后才能进行下一步操作

16. 组的管理

组是一个进程的有序集合,在实现中可以看做是进程标识符的一个有序集合,组内的每个进程与一个整数rank相联系,序列号从0开始并且是连续的.我们可以在通信组中使用组来描述通信空间中的参与者并对这些参与者进行分级.

两个特殊的预定义组:
```
MPI_GROUP_EMPTY: 空组的有效句柄,可以再组操作中作为一个参数使用
MPI_GROUP_NULL: 无效句柄,在组释放时会被返回
```

* **创建**
```c
int MPI_Comm_group(MPI_Comm comm, MPI_Group *group); 
/*建立一个通信组对应的新进程组. group返回组句柄*/
int MPI_Group_rank(MPI_Group group, int *rank); 
/*查询调用进程在进程组里的rank*/
```
说明: MPI不能凭空构造一个组,只能从其他以前定义的组中构造,最基本的组是与初始通信子MPI_COMM_WORLD相联系的组(可通过MPI_COMM_GROUP获得),其他的组均在该组基础上定义.

```c
int MPI_Group_incl(
    MPI_Group old_group,  //旧进程组
    int count,            //members数组中元素的个数 
    int *members,         //旧进程组中需要放入新进程组进程的编号
    MPI_Group *new_group  //新进程组
);
```
基于已经存在的进程组创建一个新的进程组,并指明被包含(include)的成员进程

```c
int MPI_Group_excl(
    MPI_Group old_group, 
    int count,
    int *nonmembers,
    MPI_Group *new_group
);
```
基于已经存在的进程创建一个新的进程组,并指明不被包含(exclude)的成员进程, 即新进程组包含除nonmembers之外的其它进程

* **比较**

对两个进程组判断其成员是否相同,次序是否一致.

```c
int MPI_Group_compare(
    MPI_Group group1, 
    MPI_Group group2,
    int *result
)
```
如果两个组中成员和次序完全相等,则返回**MPI_IDENT**   
如果组成员相同但次序不同,则返回**MPI_SIMILAR**   
其它情况返回**MPI_UNEQUAL**

* **相对编号**
```c
int MPI_Group_translate_ranks(
    MPI_Group group1, 
    int count,   //进程组1中有效编号的个数
    int *ranks1, //进程组1中有效编号组成的数组
    MPI_Group group2,
    int *ranks2  //ranks1中的元素在进程组2中的对应编号
);
```
检测两个不同组中相同进程的相对编号,如果属于进程组1的某个进程的编号在ranks1中,但此进程不属于进程组2,则在ranks2中对应ranks1的位置返回值为MPI_UNDEFINED;若此进程属于进程组2,则在ranks2中对应ranks1的位置返回此进程在进程组2中的编号

* **集合类操作**
```c
int MPI_Group_union( //进程组的集合并操作
    MPI_Group group1,
    MPI_Group group2,
    MPI_Group *newgroup
);

int MPI_Group_intersection( //进程组的集合交操作
    MPI_Group group1, 
    MPI_Group group2,
    MPI_Group *newgroup
);

int MPI_Group_defference(  //newgroup=group2-group1
/*进程组的集合补操作, 返回group1在group2中的相对补集*/
    MPI_Group group1,
    MPI_Group group2,
    MPI_Group *newgroup
);
```

* **释放**

```
int MPI_Group_free(MPI_Group *group);
```
释放指定进程组,组句柄被置为MPI_GROUP_NULL  

函数允许任何正在使用此组的操作正常完成

17. 通信子的管理

* **复制**
```c
int MPI_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm);
```

* **创建**
```c
int MPI_Comm_creeate(
    MPI_Comm comm,   //旧通信子
    MPI_Group group, //与comm相关联的组或其子集
    MPI_Comm *new_comm //新通信子
);
```
用由group所定义的通信组及一个新的上下文创建了一个新的通信自new_comm,对于不在group中的进程,函数返回MPI_COMM_NULL,所以新的通信子中包含group中的进程

* **划分**
```c
int MPI_Comm_split(
    MPI_Comm comm, //旧的通信子,即被划分的域
    int color,  //子域的标识,被划分出来的每个子域都对应一个color,每个子域包含具有同样color的所有进程
    int key, //每个子域内,进程按照key所定义的值的次序进行排列
    MPI_Comm *new_comm
);
```
函数将与comm相关的域划分为若干不相连的子域,根据color和key参数决定每个进程所处的位置

* **释放**
```c
int MPI_Comm_free(MPI_Comm *comm)
```
将指定通信子的句柄置为MPI_COMM_NULL,任何使用此通信子的挂起操作都会正常完成;仅当没有对此对象的活动引用时,它才会被实际撤销




