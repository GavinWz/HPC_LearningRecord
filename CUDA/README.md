## CUDA Learning Record

随着显卡的发展,GPU越来越强大,在计算上已经超过了通用的CPU.为了更大限度的利用GPU的运算能力,NVIDIA推出CUDA, 使得显卡可以用与图像计算之外的目的.

我们用host只带CPU及其内存, 用device指代GPU及其内存.CUDA程序中既包含host程序又包含device程序,他们分别在CPU和GPU上运行. 同时,host与device之间可以进行通信.

GPU并行化的工作流程:

* CPU发送一种成为kernel(核函数)的函数到GPU.
* 核函数中的线程常组织为若干干个线程块(thread block)，每个线程块中有若干个线程(thread)。
* 核函数中的全部线程块构成一个网格(grid)，线程块的个数记为网格大小(grid size)，每个线程块中有同样数目的线程，该数目称为线程块大小(block size)。

__global__是CUDA C/C++的函数修饰符, 表示该函数为一个kernel函数, 且:
* 该函数会在GPU(device)上执行
* 必须返回void
* 由主机(host)代码调用:``fun_name<<<grid_size, block_size>>>``
* 在调用kernel函数时,函数名后的<<<grid_size, block_size>>>
    * gird_size表示网格大小
    * block_size表示线程块大小

1. 线程索引
在核函数内部，程序将配置参数gird_size和block_size这两个参数值分别保存于如下两个内建变量(built-in variable)中：
* gridDim.x: 数值于grid_size相等
* blockDim.x: 数值与block_size相等
类似地，在核函数中预定义了如下表示线程的内建变量：
* blockIdx.x: 指定一个线程在网格中的线程块指标，取值范围是从0到gridDim.x-1。
* threadIdx.x: 指定一个线程在线程块中的线程指标，取值范围是从0到blockDim.x-1。


