## CUDA Learning Record

随着显卡的发展,GPU越来越强大,在计算上已经超过了通用的CPU.为了更大限度的利用GPU的运算能力,NVIDIA推出CUDA, 使得显卡可以用与图像计算之外的目的.

我们用host只带CPU及其内存, 用device指代GPU及其内存.CUDA程序中既包含host程序又包含device程序,他们分别在CPU和GPU上运行. 同时,host与device之间可以进行通信.

GPU并行化的工作流程:

* CPU发送一种成为kernel的函数到GPU.
* GPU同时运行该函数的更多个版本,成为``threads``. thread可以组合成``block``,一个kernel里的所有thread成为一个``grid``

__global__是CUDA C/C++的函数修饰符, 表示该函数为一个kernel函数, 且:
* 该函数会在GPU(device)上执行
* 必须返回void
* 由主机(host)代码调用:``fun_name<<<b, t>>>``
* 在调用kernel函数时,函数名后的<<<b, t>>>
    * b表示block的数目
    * t表示每个block中thread的数目

