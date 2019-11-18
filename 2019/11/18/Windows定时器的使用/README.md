<!--
{
	"author": "lxf",
	"title": "Windows定时器的使用",
	"date": "2019-11-18 23:28:53",
	"category": "Windows核心编程"
}
-->

Windows定时器的使用
------------------------------------------------------------
2019-11-18 23:28:53 &emsp;   


+ 创建定时器队列：`HANDLE CreateTimerQueue();`
+ 删除定时器队列：
	```
	BOOL DeleteTimerQueueEx(
	HANDLE TimerQueue,
	HANDLE CompletionEvent
	);
	```
+ 创建定时器：
	```
	BOOL CreateTimerQueueTimer(
	PHANDLE             phNewTimer,  
	HANDLE              TimerQueue,  
	WAITORTIMERCALLBACK Callback,
	PVOID               DueTime,
	DWORD               Period,
	DWORD               Flags,
	ULONG               Parameter
	);
	```
+ 删除定时器队列定时器：
	```
	BOOL DeleteTimerQueueTimer(
	HANDLE TimerQueue,
	HANDLE Timer,
	HANDLE CompletionEvent
	);
	```
+ 修改计时器对象周期：
	```
	BOOL ChangeTimerQueueTimer(
	HANDLE TimerQueue,
	HANDLE Timer,
	ULONG  DueTime,
	ULONG  Period
	);
   ```

参考资料  
[1] [CreateTimerQueue function](https://docs.microsoft.com/zh-cn/windows/win32/api/threadpoollegacyapiset/nf-threadpoollegacyapiset-createtimerqueue)  
[2] [DeleteTimerQueueEx function](https://docs.microsoft.com/zh-cn/windows/win32/api/threadpoollegacyapiset/nf-threadpoollegacyapiset-deletetimerqueueex)  
[3] [CreateTimerQueueTimer function](https://docs.microsoft.com/zh-cn/windows/win32/api/threadpoollegacyapiset/nf-threadpoollegacyapiset-createtimerqueuetimer?redirectedfrom=MSDN)  
[4] [DeleteTimerQueueTimer function](https://docs.microsoft.com/zh-cn/windows/win32/api/threadpoollegacyapiset/nf-threadpoollegacyapiset-deletetimerqueuetimer)  
[5] [ChangeTimerQueueTimer function](https://docs.microsoft.com/zh-cn/windows/win32/api/threadpoollegacyapiset/nf-threadpoollegacyapiset-changetimerqueuetimer)

------------------------------------------------------------
[返回上级目录](./../../../../categories/Windows核心编程/README.md)&emsp;|&emsp;[返回首页](./../../../../README.md)