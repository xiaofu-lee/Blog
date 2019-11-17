<!--
{
	"author": "lxf",
	"title": "Windows多线程安全之临界区",
	"date": "2019-10-15 12:13:23",
	"category": "Windows核心编程"
}
-->

Windows多线程安全之临界区
------------------------------------------------------------
### 临界区（Critical Section）
保证在某一时刻只有一个线程能访问数据的简便办法。在任意时刻只允许一个线程对共享资源进行访问。如果有多个线程试图同时访问临界区，那么在有一个线程进入后其他所有试图访问此临界区的线程将被挂起，并一直持续到进入临界区的线程离开。临界区在被释放后，其他线程可以继续抢占，并以此达到用原子方式操作共享资源的目的。

临界区包含两个操作原语： EnterCriticalSection（） 进入临界区 LeaveCriticalSection（） 离开临界区  

EnterCriticalSection（）语句执行后代码将进入临界区以后无论发生什么，必须确保与之匹配的LeaveCriticalSection（）都能够被执行到。否则临界区保护的共享资源将永远不会被释放。在使用临界区时，一般不允许其运行时间过长，只要进入临界区的线程还没有离开，其他所有试图进入此临界区的线程都会被挂起而进入到等待状态，并会在一定程度上影响。程序的运行性能。尤其需要注意的是不要将等待用户输入或是其他一些外界干预的操作包含到临界区。如果进入了临界区却一直没有释放，同样也会引起其他线程的长时间等待。换句话说，在执行了EnterCriticalSection（）语句进入临界区后无论发生什么，必须确保与之匹配的LeaveCriticalSection（）都能够被执行到。可以通过添加结构化异常处理代码来确保LeaveCriticalSection（）语句的执行。虽然临界区同步速度很快，但却只能用来同步本进程内的线程，而不可用来同步多个进程中的线程。  
 
临界区代码实例如下连接：  
[CriticalSection.h](./CriticalSection/CriticalSection.h)  
[CriticalSection.cpp](./CriticalSection/CriticalSection.cpp)  
[main.cpp](./CriticalSection/main.cpp)  
------------------------------------------------------------
[返回上级目录](./../../../../categories/Windows核心编程/README.md)  |
[返回首页](./../../../../README.md)