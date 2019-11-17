<!--
{
	"author": "lxf",
	"title": "Windows多线程安全之事件",
	"date": "2019-10-15 12:16:50",
	"category": "Windows核心编程"
}
-->

Windows多线程安全之事件
------------------------------------------------------------
### 事件（Event）
事件对象也可以通过通知操作的方式来保持线程的同步。并且可以实现不同进程中的线程同步操作。

信号量包含的几个操作原语： 
CreateEvent（） 创建一个信号量 
OpenEvent（） 打开一个事件 
SetEvent（） 回置事件 
WaitForSingleObject（） 等待一个事件 
WaitForMultipleObjects（）　等待多个事件

事件内核对象则可以对进程外的线程进行同步，其前提是得到对此事件对象的访问权。可以通过OpenEvent（）函数获取得到，其函数原型为：
```
HANDLE OpenEvent(
　DWORD dwDesiredAccess, // 访问标志
　BOOL bInheritHandle, // 继承标志
　LPCTSTR lpName // 指向事件对象名的指针
);
```
如果事件对象已创建（在创建事件时需要指定事件名），函数将返回指定事件的句柄。对于那些在创建事件时没有指定事件名的事件内核对象，可以通过使用内核对象的继承性或是调用DuplicateHandle（）函数来调用CreateEvent（）以获得对指定事件对象的访问权。在获取到访问权后所进行的同步操作与在同一个进程中所进行的线程同步操作是一样的。
    
事件代码实例如下连接：  
[Event.h](./Event/Event.h)  
[Event.cpp](./Event/Event.cpp)  
[main.cpp](./Event/main.cpp)

---
------------------------------------------------------------
[返回上级目录](./../../../../categories/Windows核心编程/README.md)  |
[返回首页](./../../../../README.md)