<!--
{
	"author": "lxf",
	"title": "汇编实现临界区自旋锁",
	"date": "2019-10-15 11:58:44",
	"category": "Windows核心编程"
}
-->

汇编实现临界区自旋锁
------------------------------------------------------------
并发是指多个线程在同时执行：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
单核是分时执行，（不是真正的同事执行）  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
多核（在某一时刻，会同时有多个线程在执行）  
同步则是保证在并发执行的环境中各个线程可以有序的执行  

**临界区汇编代码实现**
```
全局变量：flag = 0
进入临界区：
section:
    mov eax, 1
    lock xadd [flag], eax ; xadd 先交换后加1 lock 内存地址锁前缀，保证这条指令同一时刻只能有一个CPU访问 
    cmp eax,0 ; 判断eax值 为1说明有线程进入临界区
    jz endsection ; 为零跳转
    lock dec [flag] ; -1恢复
    ; 线程等待Sleep 发生线程切换
endsection:
    ret
```

**windows自旋锁汇编代码实现 单核情况下无意义**
```
1234    lock bts dword ptr [ecx], 0     ;bst指令：设置并检测，将ECX指向地址的数据的第0位置1
如果[ECX]原来的值==0，那么CF=1否则CF=0
        jb short 5678 ;跳转到 5678地址处的指令执行
        ret 4

5678    test dword ptr [ecx], 1
        jz short 1234    ;[ecx]=0时跳转
        pause       ;CPU空转，什么都不做，即不切换线程
        jmp short 5678 
```
------------------------------------------------------------
[返回上级目录](./../../../../categories/Windows核心编程/README.md)  |
[返回首页](./../../../../README.md)