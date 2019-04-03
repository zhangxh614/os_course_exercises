#lec11: 进程／线程概念spoc练习

## 视频相关思考题

### 11.1 进程的概念

1. 什么是程序？什么是进程？
   - 程序是有序代码的集合
   - 进程是指一个具有一定独立功能的程序在一个数据集合上的一次动态执行过程


2. 进程有哪些组成部分？
   - 程序，数据和进程控制块


3. 请举例说明进程的独立性和制约性的含义。
   - 独立性：不同的进程的工作不互相影响，如同时运行的浏览器和文件编辑器互不影响
   - 制约性：因访问共享数据/资源或进程间同步产生制约，如读写同一个文件


4. 程序和进程联系和区别是什么？
   - 联系：进程是执行中的程序，同一个程序的多次执行过程对应多个进程
   - 区别：进程是动态的，程序是静态的。进程是暂时的，程序是永久的。进程和程序的组成不同。


### 11.2 进程控制块

1. 进程控制块的功能是什么？
   - 管理控制进程运行所用的信息集合
   - 描述进程的基本情况以及运行变化的过程


2. 进程控制块中包括什么信息？
   - 进程标识信息
   - 处理机现场保存
   - 进程控制信息


3. ucore的进展控制块数据结构定义中哪些字段？有什么作用？
   - enum proc_state state;                                // Process state
   - int pid;                                                             // Process ID
   - int runs;                                                           // the running times of Proces
   - uintptr_t kstack;                                             // Process kernel stack
   - volatile bool need_resched;                         // bool value: need to be rescheduled to release CPU?
   - struct proc_struct *parent;                           // the parent process
   - struct mm_struct *mm;                                // Process's memory management field
   - struct context context;                                  // Switch here to run process
   - struct trapframe *tf;                                      // Trap frame for current interrupt
   - uintptr_t cr3;                                                   // CR3 register: the base addr of Page Directroy Table(PDT)
   - uint32_t flags;                                                 // Process flag
   - char name[PROC_NAME_LEN + 1];             // Process name
   - list_entry_t list_link;                                       // Process link list 
   - list_entry_t hash_link;                                   // Process hash list


### 11.3 进程状态

1. 进程生命周期中的相关事件有些什么？它们对应的进程状态变化是什么？
   - 进程创建：创建->就绪
   - 进程执行：就绪->运行
   - 进程等待：运行->等待
   - 进程抢占：运行->就绪
   - 进程唤醒：等待->就绪
   - 进程结束：运行->退出


### 11.4 三状态进程模型

1. 运行、就绪和等待三种状态的含义？7个状态转换事件的触发条件是什么？
   - 运行：进程正在处理机上运行
   - 就绪：进程获得了除处理机之外的所需资源，得到处理机即可运行
   - 等待：进程正在等待某一事件的出现而暂停运行
   - 触发条件：启动、进入就绪队列、被调度、时间片完、等待事件、事件发生、结束


### 11.5 挂起进程模型

1. 引入挂起状态的目的是什么？
   - 减少进程占用的内存
2. 引入挂起状态后，状态转换事件和触发条件有什么变化？
   - 增加就绪挂起和等待挂起两个状态
   - 增加激活和挂起两个触发条件
3. 内存中的什么内容放到外存中，就算是挂起状态？
   - 进程内核栈

### 11.6 线程的概念

1. 引入线程的目的是什么？
   - 实体之间可以并发执行
   - 实体之间共享相同的地址空间
2. 什么是线程？
   - 线程用来描述指令流的执行状态
   - 它是进程中指令执行的最小单元，是CPU调度的基本单位
3. 进程与线程的联系和区别是什么？
   - 联系：一个进程中可以同时存在多个线程
   - 区别：
     - 进程是资源分配单元，线程是CPU调度单位
     - 进程拥有一个完整的资源平台，而线程只独享指令流执行的必要资源
     - 线程并发执行的时间和空间开销小于进程（创建、切换、终止的时间，线程可共享内存和文件资源）

### 11.7 用户线程

1. 什么是用户线程？
   - 由一组用户级的线程库函数来完成线程的管理，包括线程的创建、终止、同步和调度等
2. 用户线程的线程控制块保存在用户地址空间还是在内核地址空间？
   - 用户地址空间


### 11.8 内核线程

1. 用户线程与内核线程的区别是什么？
   - 用户线程依赖用户级的函数库; 内核线程依赖系统调用实现线程机制
   - 用户线程TCB由线程库函数维护，保存在用户地址空间; 内核线程TCB由内核维护，保存在内核地址空间
   - 同一进程内的用户线程切换速度更快; 而内核线程的创建、终止和切换开销较大
   - 用户线程发起系统调用而阻塞时，整个进程进入等待; 内核线程执行系统调用而被阻塞不影响其他线程
   - 用户线程不支持基于线程的处理机抢占，只能按进程分配CPU时间; 内核线程可以以线程为单位进行CPU的时间分配
2. 同一进程内的不同线程可以共用一个相同的内核栈吗？
   - 用户线程可以
3. 同一进程内的不同线程可以共用一个相同的用户栈吗？
   - 不可以


## 选做题
1. 请尝试描述用户线程堆栈的可能维护方法。

## 小组思考题
(1) 熟悉和理解下面的简化进程管理系统中的进程状态变化情况。
 - [简化的三状态进程管理子系统使用帮助](https://github.com/chyyuu/os_tutorial_lab/blob/master/ostep/ostep7-process-run.md)
 - [简化的三状态进程管理子系统实现脚本](https://github.com/chyyuu/os_tutorial_lab/blob/master/ostep/ostep7-process-run.py)

(2) (spoc)设计一个简化的进程管理子系统，可以管理并调度如下简化进程。在理解[参考代码](https://github.com/chyyuu/ucore_lab/blob/master/related_info/lab4/process-concept-homework.py)的基础上，完成＂YOUR CODE"部分的内容。然后通过测试用例和比较自己的实现与往届同学的结果，评价自己的实现是否正确。可２个人一组。

### 进程的状态 

 - RUNNING - 进程正在使用CPU
 - READY   - 进程可使用CPU
 - DONE    - 进程结束

### 进程的行为
 - 使用CPU, 
 - 发出YIELD请求,放弃使用CPU


### 进程调度
 - 使用FIFO/FCFS：先来先服务,
   - 先查找位于proc_info队列的curr_proc元素(当前进程)之后的进程(curr_proc+1..end)是否处于READY态，
   - 再查找位于proc_info队列的curr_proc元素(当前进程)之前的进程(begin..curr_proc-1)是否处于READY态
   - 如都没有，继续执行curr_proc直到结束

### 关键模拟变量
 - 进程控制块
```
PROC_CODE = 'code_'
PROC_PC = 'pc_'
PROC_ID = 'pid_'
PROC_STATE = 'proc_state_'
```
 - 当前进程 curr_proc 
 - 进程列表：proc_info是就绪进程的队列（list），
 - 在命令行（如下所示）需要说明每进程的行为特征：（１）使用CPU ;(2)等待I/O
```
   -l PROCESS_LIST, --processlist= X1:Y1,X2:Y2,...
   X 是进程的执行指令数; 
   Ｙ是执行CPU的比例(0..100) ，如果是100，表示不会发出yield操作
```
 - 进程切换行为：系统决定何时(when)切换进程:进程结束或进程发出yield请求

### 进程执行
```
instruction_to_execute = self.proc_info[self.curr_proc][PROC_CODE].pop(0)
```

### 关键函数
 - 系统执行过程：run
 - 执行状态切换函数:　move_to_ready/running/done　
 - 调度函数：next_proc

### 执行实例

#### 例１
```
$./process-simulation.py -l 5:50
Process 0
  yld
  yld
  cpu
  cpu
  yld

Important behaviors:
  System will switch when the current process is FINISHED or ISSUES AN YIELD
Time     PID: 0 
  1     RUN:yld 
  2     RUN:yld 
  3     RUN:cpu 
  4     RUN:cpu 
  5     RUN:yld 

```


#### 例２
```
$./process-simulation.py  -l 5:50,5:50
Produce a trace of what would happen when you run these processes:
Process 0
  yld
  yld
  cpu
  cpu
  yld

Process 1
  cpu
  yld
  cpu
  cpu
  yld

Important behaviors:
  System will switch when the current process is FINISHED or ISSUES AN YIELD
Time     PID: 0     PID: 1 
  1     RUN:yld      READY 
  2       READY    RUN:cpu 
  3       READY    RUN:yld 
  4     RUN:yld      READY 
  5       READY    RUN:cpu 
  6       READY    RUN:cpu 
  7       READY    RUN:yld 
  8     RUN:cpu      READY 
  9     RUN:cpu      READY 
 10     RUN:yld      READY 
 11     RUNNING       DONE 
```
