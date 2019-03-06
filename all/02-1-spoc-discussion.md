# lec 3 SPOC Discussion

## **提前准备**
（请在上课前完成）


 - 完成lec3的视频学习和提交对应的在线练习
 - git pull ucore_os_lab, v9_cpu, os_course_spoc_exercises  　in github repos。这样可以在本机上完成课堂练习。
 - 仔细观察自己使用的计算机的启动过程和linux/ucore操作系统运行后的情况。搜索“80386　开机　启动”
 - 了解控制流，异常控制流，函数调用,中断，异常(故障)，系统调用（陷阱）,切换，用户态（用户模式），内核态（内核模式）等基本概念。思考一下这些基本概念在linux, ucore, v9-cpu中的os*.c中是如何具体体现的。
 - 思考为什么操作系统需要处理中断，异常，系统调用。这些是必须要有的吗？有哪些好处？有哪些不好的地方？
 - 了解在PC机上有啥中断和异常。搜索“80386　中断　异常”
 - 安装好ucore实验环境，能够编译运行lab8的answer
 - 了解Linux和ucore有哪些系统调用。搜索“linux 系统调用", 搜索lab8中的syscall关键字相关内容。在linux下执行命令: ```man syscalls```
 - 会使用linux中的命令:objdump，nm，file, strace，man, 了解这些命令的用途。
 - 了解如何OS是如何实现中断，异常，或系统调用的。会使用v9-cpu的dis,xc, xem命令（包括启动参数），分析v9-cpu中的os0.c, os2.c，了解与异常，中断，系统调用相关的os设计实现。阅读v9-cpu中的cpu.md文档，了解汇编指令的类型和含义等，了解v9-cpu的细节。
 - 在piazza上就lec3学习中不理解问题进行提问。

## 第三讲 启动、中断、异常和系统调用-思考题

## 3.1 BIOS
-  请描述在“计算机组成原理课”上，同学们做的MIPS CPU是从按复位键开始到可以接收按键输入之间的启动过程。
   -  设置段寄存器、寄存器、CP0寄存器等寄存器的初始值。
   -  将PC值指向系统的第一条指令
-  x86中BIOS从磁盘读入的第一个扇区是是什么内容？为什么没有直接读入操作系统内核映像？
   -  主引导记录。
   -  磁盘上文件系统多种多样，BIOS适配所有文件系统是不现实的，故BIOS无法直接读取并加载内核的镜像。且一个计算机中可能不只一个分区，BIOS无法判断从哪个分区启动，故BIOS读取固定位置的主引导记录，由它再做判断。
-  比较UEFI和BIOS的区别。
   - UEFI 使用独立的分区，将系统启动文件和操作系统隔离开来，更加安全
   - UEFI 启动时可调用EFIShell，可以加载指定的硬件驱动和选择启动文件
   - UEFI 可支持引导2TB以上的硬盘
-  理解rcore中的Berkeley BootLoader (BBL)的功能。
   -  处理RISC-V处理器无法直接在硬件中处理的任何非法指令
   -  启动并响应时钟中断
   -  处理未对齐的内存访问（目前已弃用）
   -  支持Linux启动时的链式加载和初始化终端访问，简化第一阶段的加载程序

## 3.2 系统启动流程

- x86中分区引导扇区的结束标志是什么？
  - 0x55AA
- x86中在UEFI中的可信启动有什么作用？
  - 启动前检查数字签名来包保证启动介质安全性
- RV中BBL的启动过程大致包括哪些内容？
  - 筛选 Device Tree Blob
  - （打印 logo）
  - （打印 Device Tree Blob）
  - 启动其他 hart

## 3.3 中断、异常和系统调用比较
- 什么是中断、异常和系统调用？
  - 中断：外设触发
  - 异常：应用程序意想不到的行为触发
  - 系统调用：应用程序请求操作提供服务
- 中断、异常和系统调用的处理流程有什么异同？
  - 同：进入异常处理程序，切换到内核态
  - 异：
    - 源头：中断来源于外设，异常和系统调用来源于应用程序
    - 响应方式：中断-异步，异常-同步，系统调用-同步或异步
- 以ucore/rcore lab8的answer为例，ucore的系统调用有哪些？大致的功能分类有哪些？
  - 进程管理： fork / exit / wait / exec / yield / kill / getpid / sleep
  - 文件操作：open / close / read / write / seek / fstat / fsync / getcwd / getdirentry / dup
  - 内存管理：pgdir
  - 外设输出：putc

## 3.4 linux系统调用分析
- 通过分析[lab1_ex0](https://github.com/chyyuu/ucore_lab/blob/master/related_info/lab1/lab1-ex0.md)了解Linux应用的系统调用编写和含义。(仅实践，不用回答)
- 通过调试[lab1_ex1](https://github.com/chyyuu/ucore_lab/blob/master/related_info/lab1/lab1-ex1.md)了解Linux应用的系统调用执行过程。(仅实践，不用回答)


## 3.5 ucore/rcore系统调用分析 （扩展练习，可选）
-  基于实验八的代码分析ucore的系统调用实现，说明指定系统调用的参数和返回值的传递方式和存放位置信息，以及内核中的系统调用功能实现函数。
- 以ucore/rcore lab8的answer为例，分析ucore 应用的系统调用编写和含义。
- 以ucore/rcore lab8的answer为例，尝试修改并运行ucore OS kernel代码，使其具有类似Linux应用工具`strace`的功能，即能够显示出应用程序发出的系统调用，从而可以分析ucore应用的系统调用执行过程。


## 3.6 请分析函数调用和系统调用的区别
- 系统调用与函数调用的区别是什么？
  - 系统调用使用INT和IRET指令，函数调用使用CALL和RET指令
  - 系统调用有堆栈和特权级的转换，函数无
  - 系统调用涉及特权级的转换，时间开销大。函数调用有时需要更大的空间开销。
- 通过分析x86中函数调用规范以及`int`、`iret`、`call`和`ret`的指令准确功能和调用代码，比较x86中函数调用与系统调用的堆栈操作有什么不同？
  - 当保护级别不变时，int 指令将 EFLAGS、CS、EIP、Error Code依次压栈，当保护级别改变时，int 指令将 SS、ESP、EFLAGS、CS、EIP、Error Code 依次压栈。iret 时则将压栈的内容恢复。
  - call 和 ret 只需将返回地址压栈和恢复。
- 通过分析RV中函数调用规范以及`ecall`、`eret`、`jal`和`jalr`的指令准确功能和调用代码，比较x86中函数调用与系统调用的堆栈操作有什么不同？
  - jal 和 jalr 都将 PC+4 存入 $ra，jalr 跳转到 \$r 寄存器的位置
  - ecall 和 eret 的调用都需要额外修改 mstatus 寄存器来完成特权级的转换。


## 课堂实践 （在课堂上根据老师安排完成，课后不用做）
### 练习一
通过静态代码分析，举例描述ucore/rcore键盘输入中断的响应过程。

### 练习二
通过静态代码分析，举例描述ucore/rcore系统调用过程，及调用参数和返回值的传递方法。
