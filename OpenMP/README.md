## OpenMP Learning Record
在C/C++中, OpenMP可以通过使用预处理指令来让程序并行化, OpenMP指令使用的格式为:
```c
#pragma omp 指令
```

1. time.clock()与omp_get_wtime()

clock()函数返回从“开启这个程序进程”到“程序中调用clock()函数”时之间的CPU时钟计时单元(clock
tick)数, 在omp程序中多个线程同时运行, 用clock计时并不能得到想要的结果.

omp_get_wtime()函数返回从某一时间点到调用时所经过的时间

2. for指令
for指令的作用是使一个for循环在多个线程中执行, 一般for指令与parallel指令同时使用, 即parallel for. 此外还可以在parallel指令的并行块中单独使用, 在一个并行快中可以使用多个for指令. 但是单独使用for指令是没有效果的.

3. parellel指令
parallel是构造并行块的指令, 同时也可以配合其它指令如for, sections等一起使用. 在这个指令后需要使用一对大括号来制定并行代码块.
```c
#pragma omp parallel [for | sections] [子句[子句]...]
{
    //并行代码
}
```
4. num_threads(thread_num)
```c
#pragma omp parallel num_threads(thread_num)
```
指定执行此代码块的线程数量

5. omp_get_num_procs()
返回调用函数时, 可用的线程数目

5. omp_get_num_threads()
返回当前并行区域中的活动线程个数, 若在并行区域之外调用则返回0

5. sections和section
sections语句指定一个并行代码块, 并用section语句将此代码块分为多个分块, 各个分块并行执行
```c
#pragma omp parallel sections
{
    #pragma omp section
    {
        //section1
    }
    #pragma omp section
    {
        //section2
    }
    ...
}
```

6. omp_in_parallel
判断当前是否处于并行状态, 返回1表示是, 返回0表示否. 

6. private子句

* private
将变量声明为线程私有, 声明私有之后,每个线程都获得一个该变量的副本, 线程之间不会相互影响, 各自之间不能相互访问对方的私有变量, 且原变量在并行部分不起任何作用, 值也不会因为并行代码块中的操作而改变

```c
#pragma omp parallel [for|section] private(value)
{
    ...
}
```
* firstprivate

功能与private类似, firstprivate可继承变量原来的值, 但不保留操作后的值

* lastprivate

将变量操作后的值保存下来带出并行代码块, 需要注意的是, 根据OpenMP规范:  
1. 在循环迭代中, 是最后一次迭代的值赋给原变量
2. 在section结构中 ,是程序语法上的最后一个section语句的结果赋原变量
3. 如果是类(class)变量作为lastprivate的参数时, 我们需要一个缺省构造函数, 除非该变量也作为子句的参数;此外还需要拷贝一个赋值操作符

* threadprivate

将一个变量分别复制一份拷贝给各个线程, 作为各个线程的私有变量, 即各个线程具有各自私有的全局对象, 而不止在并行代码块中有效.  
此变量只能为全局变量或静态变量(static), 且threadprivate语句要紧跟在变量声明的后边

7. shared
将一个变量声明为共享变量, 并在多个线程内共享. 程序分配一块单独的内存给这个变量, 所有的并行线程共享这块内存空间. 在并行部分进行写操作时, 要求对共享变量进行保护, 否则不要随便使用共享变量, 尽量将共享变量换为私有变量使用.

8. reduction
对一个或多个参数指定一个操作符, 然后每一个线程都会创建这个参数的私有拷贝, 在各自的线程中对其进行操作, 在并行区域结束后, 迭代指定的运算符, 并更新原参数值.
```c
reduction(operator: list);
//operator为操作符, list为一个变量或多个变量组成的数组*/
```

9. copyin
将主线程中的变量值拷贝到各个线程的私有变量中, 但是主线程中的变量值不会改变.  
只有被声明为threadprivate的变量才可作为copyin子句的参数

10. 循环调度: schedule
schedule只能用于循环并行构造中, 作用是控制循环并行结构的任务调度, 将循环迭代分配给各个线程. 
语法为:``schedule(kind[, chunk_size])``
* 静态调度static

schedule(static, size): size为每个线程分配的迭代数, 若不给出size参数, 则程序将迭代数/总线程数作为size的值

"静态"体现在这个调度过程跟程序的实际运行无关, 可以指定或推理出那几次迭代在哪几个线程中运行
在用户没有使用schedule子句的并行循环中, 系统默认采用static方式进行调度. 

* 动态调度dynamic
schedule(dynamic, size)
动态调度依赖程序运行状态, 无法预知哪次迭代在哪个线程中运行. 

在没有指定size的情况下, 各个线程按照执行完即分配的方式进行调度, 只要还有迭代没有完成, 哪个线程开始空闲就将下一次迭代分配给它, 直到完成循环迭代

指定的size参数表示每次分配给线程的迭代次数, 默认size为1

* guided调度
```
schedule(guided, size)
```
类似与动态调度, 但是每次分配的迭代次数不同. 设每次分配的迭代次数为n, 则n会随着每次分配逐渐减小, size表示n的最小值, 即当n减小到size时将不在减小, 无论是否已经分配完. 默认size为1

* runtime

runtime表示根据环境变量确定上述调度策略中的某一种, 默认也是静态的(static). 

控制schedule环境变量的是OMP_SCHEDULE环境变量, 值为上面三种类型的一种, 例如:  
OMP_SCHEDULE="dynamic, 5"  
表示schedule(dynamic, 5)