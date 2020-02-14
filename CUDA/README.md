## CUDA Learning Record

随着显卡的发展,GPU越来越强大,在计算上已经超过了通用的CPU.为了更大限度的利用GPU的运算能力,NVIDIA推出CUDA, 使得显卡可以用与图像计算之外的目的.

程序中用host指代CPU及其内存, 用device指代GPU及其内存.CUDA程序中既包含host程序又包含device程序,他们分别在CPU和GPU上运行. 同时,host与device之间可以进行通信.

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

2. 多维网格
* unit3：
    blockIdx和threadIdx是类型为unit3的结构体变量，该结构体共有三个成员变量x，y，z。
* gridDim：
    gridDim和blockDim是类型为dim3的结构体变量，该结构体共有三个成员变量x，y，z。
这些内建变量均只在核函数中有效（可见）。在调用核函数时的执行配置中：  

``<<<grid_size, block_size>>>``  

grid_size和block_size的值被分别赋给内建变量gridDim.x和blockDim.x，此时，girdDim和blockDim中没有被指定的成员y和z取默认值1。在这种情况下，网格和线程块均为“一维”的。

* 构造多维网格和线程块：
因为gird_size和block_size均为dim3结构体类型，所以可以通过结构体dim3来定义多维的网格和线程块（用到了C++中构造函数的语法）：
```c
dim3 grid_size(Gx ,Gy, Gz);
dim3 block_size(Bx, By, Bz);
```
表示一维时，y和z可省略
表示二维时，z可省略

多维线程块本质上还是一维的，与多维线程指标threadId.x, threadIdy, threadId.z对应的一维线程指标为：  

``tid = threadId.x * blockDim.x + threadId.y * blockDim.y + threadId.z * blickDim.z;``

与多维线程块指标blockIdx.x, blockIdx.y, blockIdx.z相关联的线程块指标为：

``bid = blockIdx.z * girdDim.x * gridDim.y + blockIdx.y * gridDim.x + blockIdx.x;``

* 网格与线程块大小的限制

网格大小(grid_size)在x、y、z三个方向的最大允许值分别为2^(31-1)、65535/65535

线程块大小(thread_size)在x、y、z三个方向的最大允许值分别为1024、1024、64。且blockDim.x、 blockDim.y、blockDim.z的乘积不能大于1024，即无论如何分配，一个线程块最多只能有1024个线程。

3. nvcc的编译过程
CUDA的编译器驱动nvcc先将全部源代码分离为主机(host)代码和设备(device)代码。主机代码完全支持C++语法，而设备代码只是部分支持。

nvcc先将设备代码编译为PTX(Parallel Thread Execution)伪汇编代码，再将PTX代码编译为二进制的cubin目标代码

在将源代码编译为PTX代码时，需要用选项**-arch=cumpute_XY**指定一个虚拟架构的计算能力，以确定代码中能够使用的CUDA功能。

在将PTX代码编译为cubin代码时，需要用选项**-code=sm_ZW**指定一个真实架构的计算能力，以确定可执行文件能使用的GPU。指定了GPU的真实架构为Z.W,对应的可执行文件只能在主版本号为Z、次版本号大于等于W的GPU中运行。

真实架构的计算能力必须大于虚拟架构的计算能力

4. CUDA程序的基本框架

```c
头文件包含
宏定义
用户函数和CUDA核函数的声明
int main(){
    分配主机与设备内存
    初始化主机中的数据
    将某些数据从主机复制到设备
    调用核函数在设备中进行计算
    将某些数据从设备复制到机
    释放主机与设备内存
}
```


