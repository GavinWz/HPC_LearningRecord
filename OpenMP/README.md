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

```c
#pragma omp parallel num_threads(thread_num)
```
指定执行此代码块的线程数量

4. sections和section
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