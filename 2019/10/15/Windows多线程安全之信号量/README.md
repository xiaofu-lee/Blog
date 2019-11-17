<!--
{
	"author": "lxf",
	"title": "Windows多线程安全之信号量",
	"date": "2019-10-15 12:26:54",
	"category": "Windows核心编程"
}
-->

Windows多线程安全之信号量
------------------------------------------------------------
### 信号量（Semaphores）
信号量对象对线程的同步方式与前面几种方法不同，信号允许多个线程同时使用共享资源，这与操作系统中的PV操作相同。它指出了同时访问共享资源的线程最大数目。它允许多个线程在同一时刻访问同一资源，但是需要限制在同一时刻访问此资源的最大线程数目。在用CreateSemaphore（）创建信号量时即要同时指出允许的最大资源计数和当前可用资源计数。一般是将当前可用资源计数设置为最大资源计数，每增加一个线程对共享资源的访问，当前可用资源计数就会减1，只要当前可用资源计数是大于0的，就可以发出信号量信号。但是当前可用计数减小到0时则说明当前占用资源的线程数已经达到了所允许的最大数目，不能在允许其他线程的进入，此时的信号量信号将无法发出。线程在处理完共享资源后，应在离开的同时通过ReleaseSemaphore（）函数将当前可用资源计数加1。在任何时候当前可用资源计数决不可能大于最大资源计数。 信号量是通过计数来对线程访问资源进行控制的，而实际上信号量确实也被称作Dijkstra计数器。

 PV操作及信号量的概念都是由荷兰科学家E.W.Dijkstra提出的。信号量S是一个整数，S大于等于零时代表可供并发进程使用的资源实体数，但S小于零时则表示正在等待使用共享资源的进程数。

    P操作申请资源： 
    （1）S减1； 
    （2）若S减1后仍大于等于零，则进程继续执行； 
    （3）若S减1后小于零，则该进程被阻塞后进入与该信号相对应的队列中，然后转入进程调度。 
　　 
    V操作 释放资源： 
    （1）S加1； 
    （2）若相加结果大于零，则进程继续执行； 
    （3）若相加结果小于等于零，则从该信号的等待队列中唤醒一个等待进程，然后再返回原进程继续执行或转入进程调度。

使用信号量内核对象进行线程同步主要会用到CreateSemaphore（）、OpenSemaphore（）、ReleaseSemaphore（）、WaitForSingleObject（）和WaitForMultipleObjects（）等函数。其中，CreateSemaphore（）用来创建一个信号量内核对象，其函数原型为：
```
HANDLE CreateSemaphore(
　LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, // 安全属性指针
　LONG lInitialCount, // 初始计数
　LONG lMaximumCount, // 最大计数
　LPCTSTR lpName // 对象名指针
);
```
参数lMaximumCount是一个有符号32位值，定义了允许的最大资源计数，最大取值不能超过4294967295。lpName参数可以为创建的信号量定义一个名字，由于其创建的是一个内核对象，因此在其他进程中可以通过该名字而得到此信号量。OpenSemaphore（）函数即可用来根据信号量名打开在其他进程中创建的信号量，函数原型如下：
```
HANDLE OpenSemaphore(
　DWORD dwDesiredAccess, // 访问标志
　BOOL bInheritHandle, // 继承标志
　LPCTSTR lpName // 信号量名
);
```
在线程离开对共享资源的处理时，必须通过ReleaseSemaphore（）来增加当前可用资源计数。否则将会出现当前正在处理共享资源的实际线程数并没有达到要限制的数值，而其他线程却因为当前可用资源计数为0而仍无法进入的情况。ReleaseSemaphore（）的函数原型为：
```
BOOL ReleaseSemaphore(
　HANDLE hSemaphore, // 信号量句柄
　LONG lReleaseCount, // 计数递增数量
　LPLONG lpPreviousCount // 先前计数
);
```
该函数将lReleaseCount中的值添加给信号量的当前资源计数，一般将lReleaseCount设置为1，如果需要也可以设置其他的值。WaitForSingleObject（）和WaitForMultipleObjects（）主要用在试图进入共享资源的线程函数入口处，主要用来判断信号量的当前可用资源计数是否允许本线程的进入。只有在当前可用资源计数值大于0时，被监视的信号量内核对象才会得到通知。

临界区代码实例如下连接：  
[Semaphores.h](./Semaphores/Semaphores.h)  
[Semaphores.cpp](./Semaphores/Semaphores.cpp)  
[main.cpp](./Semaphores/main.cpp) 
------------------------------------------------------------
[返回上级目录](./../../../../categories/Windows核心编程/README.md)  |
[返回首页](./../../../../README.md)