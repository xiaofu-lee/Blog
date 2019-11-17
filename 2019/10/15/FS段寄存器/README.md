<!--
{
	"author": "lxf",
	"title": "FS段寄存器",
	"date": "2019-10-15 11:56:42",
	"category": "Windows核心编程"
}
-->

FS段寄存器
------------------------------------------------------------
下面为FS寄存器下偏移的相关信息：   

    00 指向SEH链表指针  
    04 线程堆栈顶部（ 地址最小）  
    08 线程堆栈底部（ 地址最大）  
    0c SubSystemTib  
    10 FiberData  
    14 ArbitraryUserPointer  
    18 FS段寄存器在内存中的镜像  
    20 进程PID  
    24 线程ID  
    2c 指向线程局部存储的指针  
    30 PEB结构地址（ 进程结构 / 不是PCB进程控制块）  
    34 上一个错误（ LastError)  

汇编代码： 

```
DWORD _THREAD_STACK_SP; // 04h
DWORD _THREAD_STACK_BP; // 08h
DWORD _PID; // 20h
DWORD _TID; // 24h
DWORD _LAST_ERROR; // 34h

_asm {

    mov eax, dword ptr fs: [04 h]
    mov[_THREAD_STACK_SP], eax

    mov eax, dword ptr fs: [08 h]
    mov[_THREAD_STACK_BP], eax

    mov eax, dword ptr fs: [20 h]
    mov[_PID], eax

    mov eax, dword ptr fs: [24 h]
    mov[_TID], eax

    mov eax, dword ptr fs: [34]
    mov[_LAST_ERROR], eax
}

printf("_THREAD_STACK_SP = 0x%p\n", _THREAD_STACK_SP); 
printf("_THREAD_STACK_BP = 0x%p\n", _THREAD_STACK_BP); 
printf("_LAST_ERROR = %d\n", _LAST_ERROR); 

printf("_PID = %d , CurrentProcessId = %d\n", _PID, GetCurrentProcessId()); 
printf("_TID = %d , CurrentThreadId  = %d\n", _TID, GetCurrentThreadId()); 
```
------------------------------------------------------------
[返回上级目录](./../../../../categories/Windows核心编程/README.md)  |
[返回首页](./../../../../README.md)