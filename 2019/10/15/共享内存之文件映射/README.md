<!--
{
	"author": "lxf",
	"title": "共享内存之文件映射",
	"date": "2019-10-15 11:54:02",
	"category": "Windows核心编程"
}
-->

共享内存之文件映射
------------------------------------------------------------
共享内存主要是通过映射机制实现的。  
Windows 下进程的地址空间在逻辑上是相互隔离的，但在物理上却是重叠的。所谓的重叠是指同一块内存区域可能被多个进程同时使用。当调用 CreateFileMapping 创建命名的内存映射文件对象时，Windows 即在物理内存申请一块指定大小的内存区域，返回文件映射对象的句柄 hMap。为了能够访问这块内存区域必须调用 MapViewOfFile 函数，促使 Windows 将此内存空间映射到进程的地址空间中。当在其他进程访问这块内存区域时，则必须使用OpenFileMapping 函数取得对象句柄 hMap，并调用 MapViewOfFile 函数得到此内存空间的一个映射。这样一来，系统就把同一块内存区域映射到了不同进程的地址空间中，从而达到共享内存的目的。  
CreateFile //创建或打开文件内核对象  
CreateFileMapping //创建文件映射内核对象（OpenFileMapping， 在其它进程中， 打开文件映射对象）  
MapViewOfFile //将文件数据映射到进程的地址空间    
UnmapViewOfFile //从进程的地址空间撤销文件数据的映像  
CloseHandle //关闭文件对象和文件映射对象  

**创建共享内存进程代码如下**  
CreateShareMemoryProcess.cpp
```
#include <stdio.h>
#include <windows.h>

int main(int argc, char const *argv[])
{
    // 创建互斥体
    HANDLE hMutex = CreateMutex(NULL, TRUE, "mutex");

    HANDLE hShareMem = INVALID_HANDLE_VALUE;
    // 创建共享内存
    hShareMem = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        4,
        "ShareMemory");

    if (hShareMem && hShareMem != INVALID_HANDLE_VALUE)
    {
        // 将共享内存映射到本进程地址空间
        int *pShareAddr = (int *)MapViewOfFile(
            hShareMem,
            FILE_MAP_READ | FILE_MAP_WRITE | FILE_MAP_ALL_ACCESS,
            0, 0, 0);
        ZeroMemory(pShareAddr, 4);
        ReleaseMutex(hMutex);
        while (TRUE)
        {
            // 进入临界区
            WaitForSingleObject(hMutex, INFINITE);
            printf("mian process-->pShareAddr = %d\n", *pShareAddr);
            if (*pShareAddr == 500)
            {
                *pShareAddr = -1;
                UnmapViewOfFile(pShareAddr);
                pShareAddr = NULL;
                CloseHandle(hShareMem);
                hShareMem = INVALID_HANDLE_VALUE;
                break;
            }
            Sleep(200);
            // 释放临界区
            ReleaseMutex(hMutex);
        }
    }
    return 0;
}

```

**生产者共享内存进程代码如下**  
ProductProcess.cpp
```
#include <stdio.h>
#include <windows.h>

// 生产者进程

int main(int argc, char const *argv[])
{
    HANDLE hMutex = OpenMutexA(MUTANT_ALL_ACCESS, FALSE, "mutex");

    HANDLE hShareMem = INVALID_HANDLE_VALUE;

    // 打开共享内存
    hShareMem = OpenFileMappingA(
		FILE_MAP_ALL_ACCESS,
		FALSE,
		"ShareMemory"
	);

    if (hShareMem && hShareMem != INVALID_HANDLE_VALUE)
	{
        // 将共享内存映射到本进程地址空间
        int *pShareAddr = (int *)MapViewOfFile(hShareMem, FILE_MAP_READ | FILE_MAP_WRITE | FILE_MAP_ALL_ACCESS, 0, 0, 0);
        while (TRUE)
        {
            // 进入临界区
            WaitForSingleObject(hMutex, INFINITE);
            printf("product process-->pShareAddr = %d\n", *pShareAddr);
            (*pShareAddr)++;
            if (*pShareAddr == -1)
            {
                UnmapViewOfFile(pShareAddr);
                pShareAddr = NULL;
                CloseHandle(hShareMem);
                hShareMem = INVALID_HANDLE_VALUE;
                break;
            }
            Sleep(200);
            // 释放临界区
            ReleaseMutex(hMutex);
        }
	}
    return 0;
}

```

**消费者共享内存进程代码如下**  
ConsumerProcess.cpp
```
#include <stdio.h>
#include <windows.h>

// 消费者进程

int main(int argc, char const *argv[])
{
    HANDLE hMutex = OpenMutexA(MUTANT_ALL_ACCESS, FALSE, "mutex");

    HANDLE hShareMem = INVALID_HANDLE_VALUE;

    // 打开共享内存
    hShareMem = OpenFileMappingA(
		FILE_MAP_ALL_ACCESS,
		FALSE,
		"ShareMemory"
	);

    if (hShareMem && hShareMem != INVALID_HANDLE_VALUE)
	{
        // 将共享内存映射到本进程地址空间
        int *pShareAddr = (int *)MapViewOfFile(hShareMem, FILE_MAP_READ | FILE_MAP_WRITE | FILE_MAP_ALL_ACCESS, 0, 0, 0);
        while (TRUE)
        {
            // 进入临界区
            WaitForSingleObject(hMutex, INFINITE);
            printf("consumer process-->pShareAddr = %d\n", *pShareAddr);
            if (*pShareAddr == -1)
            {
                UnmapViewOfFile(pShareAddr);
                pShareAddr = NULL;
                CloseHandle(hShareMem);
                hShareMem = INVALID_HANDLE_VALUE;
                break;
            }
            Sleep(200);
            // 释放临界区
            ReleaseMutex(hMutex);
        }
	}
    return 0;
}

```
------------------------------------------------------------
[返回上级目录](./../../../../categories/Windows核心编程/README.md)  |
[返回首页](./../../../../README.md)