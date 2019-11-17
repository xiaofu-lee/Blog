<!--
{
	"author": "lxf",
	"title": "Windows多线程安全之互斥量",
	"date": "2019-10-15 12:10:19",
	"category": "Windows核心编程"
}
-->

Windows多线程安全之互斥量
------------------------------------------------------------
### 互斥量（Mutex）  
互斥（Mutex）是一种用途非常广泛的内核对象。能够保证多个线程对同一共享资源的互斥访问。同临界区有些类似，只有拥有互斥对象的线程才具有访问资源的权限，由于互斥对象只有一个，因此就决定了任何情况下此共享资源都不会同时被多个线程所访问。当前占据资源的线程在任务处理完后应将拥有的互斥对象交出，以便其他线程在获得后得以访问资源。与其他几种内核对象不同，互斥对象在操作系统中拥有特殊代码，并由操作系统来管理，操作系统甚至还允许其进行一些其他内核对象所不能进行的非常规操作。 互斥量跟临界区很相似，只有拥有互斥对象的线程才具有访问资源的权限，由于互斥对象只有一个，因此就决定了任何情况下此共享资源都不会同时被多个线程所访问。当前占据资源的线程在任务处理完后应将拥有的互斥对象交出，以便其他线程在获得后得以访问资源。互斥量比临界区复杂。因为使用互斥不仅仅能够在同一应用程序不同线程中实现资源的安全共享，而且可以在不同应用程序的线程之间实现对资源的安全共享。  

以互斥内核对象来保持线程同步可能用到的函数主要有CreateMutex（）、OpenMutex（）、ReleaseMutex（）、WaitForSingleObject（）和WaitForMultipleObjects（）等。在使用互斥对象前，首先要通过CreateMutex（）或OpenMutex（）创建或打开一个互斥对象。CreateMutex（）函数原型为：
```
HANDLE CreateMutex(
　LPSECURITY_ATTRIBUTES lpMutexAttributes, // 安全属性指针
　BOOL bInitialOwner, // 初始拥有者
　LPCTSTR lpName // 互斥对象名
);
```

参数bInitialOwner主要用来控制互斥对象的初始状态。一般多将其设置为FALSE，以表明互斥对象在创建时并没有为任何线程所占有。如果在创建互斥对象时指定了对象名，那么可以在本进程其他地方或是在其他进程通过OpenMutex（）函数得到此互斥对象的句柄。OpenMutex（）函数原型为：
```
HANDLE OpenMutex(
　DWORD dwDesiredAccess, // 访问标志
　BOOL bInheritHandle, // 继承标志
　LPCTSTR lpName // 互斥对象名
);
```
　
当目前对资源具有访问权的线程不再需要访问此资源而要离开时，必须通过ReleaseMutex（）函数来释放其拥有的互斥对象，其函数原型为：
```
BOOL ReleaseMutex(HANDLE hMutex);
```

其唯一的参数hMutex为待释放的互斥对象句柄。至于WaitForSingleObject（）和WaitForMultipleObjects（）等待函数在互斥对象保持线程同步中所起的作用与在其他内核对象中的作用是基本一致的，也是等待互斥内核对象的通知。但是这里需要特别指出的是：在互斥对象通知引起调用等待函数返回时，等待函数的返回值不再是通常的WAIT_OBJECT_0（对于WaitForSingleObject（）函数）或是在WAIT_OBJECT_0到WAIT_OBJECT_0+nCount-1之间的一个值（对于WaitForMultipleObjects（）函数），而是将返回一个WAIT_ABANDONED_0（对于WaitForSingleObject（）函数）或是在WAIT_ABANDONED_0到WAIT_ABANDONED_0+nCount-1之间的一个值（对于WaitForMultipleObjects（）函数）。以此来表明线程正在等待的互斥对象由另外一个线程所拥有，而此线程却在使用完共享资源前就已经终止。除此之外，使用互斥对象的方法在等待线程的可调度性上同使用其他几种内核对象的方法也有所不同，其他内核对象在没有得到通知时，受调用等待函数的作用，线程将会挂起，同时失去可调度性，而使用互斥的方法却可以在等待的同时仍具有可调度性，这也正是互斥对象所能完成的非常规操作之一。

互斥量代码实例如下连接：  
[Mutex.h](./Mutex/Mutex.h)  
[Mutex.cpp](./Mutex/Mutex.cpp)  
[main.cpp](./Mutex/main.cpp)  
------------------------------------------------------------
[返回上级目录](./../../../../categories/Windows核心编程/README.md)  |
[返回首页](./../../../../README.md)