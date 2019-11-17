<!--
{
	"author": "lxf",
	"title": "Windows平台动态执行机器码",
	"date": "2019-10-15 12:01:11",
	"category": "Windows核心编程"
}
-->

Windows平台动态执行机器码
------------------------------------------------------------
保留，提交或更改调用进程的虚拟地址空间中页面区域的状态。此功能分配的内存自动初始化为零。要在另一个进程的地址空间中分配内存，请使用 VirtualAllocEx函数。  
**语法:**
```
LPVOID VirtualAlloc(
  LPVOID lpAddress,
  SIZE_T dwSize,
  DWORD  flAllocationType,
  DWORD  flProtect
);
```
**参数**  
**lpAddress**  
要分配的区域的起始地址。如果正在保留内存，则将指定的地址向下舍入到分配粒度的最接近的倍数。如果内存已被保留并且正在提交，则地址将向下舍入到下一页边界。要确定页面大小和主机上的分配粒度，请使用 GetSystemInfo函数。如果此参数为 NULL，则系统确定分配区域的位置。  
如果此地址位于您未通过调用InitializeEnclave初始化的安全区内，则VirtualAlloc会为该地址的安全区分配一页零。该页面必须先前未提交，并且不会使用Intel Software Guard Extensions编程模型的EEXTEND指令进行测量。  
如果您初始化的安全区内的地址，则分配操作将失败，并显示ERROR_INVALID_ADDRESS错误。   

**dwSize**  
区域的大小，以字节为单位。如果lpAddress参数为 NULL，则此值将向上舍入到下一页边界。否则，分配的页面包括包含一个或多个字节的所有页面，范围从lpAddress到 lpAddress + dwSize。这意味着跨越页面边界的2字节范围会导致两个页面都包含在分配的区域中。  

**flAllocationType**  
内存分配的类型。此参数必须包含以下值之一。  

| 值 | 含义 |
|:---:|:---|
| **MEM_COMMIT** <br> 0x00001000 | 为指定的保留内存页分配内存费用（来自内存的总大小和磁盘上的页面文件）。该函数还保证当调用者最初访问内存时，内容将为零。除非/直到实际访问虚拟地址，否则不会分配实际物理页面。<br>要一步保留和提交页面，请使用以下命令调用VirtualAllocMEM_COMMIT | MEM_RESERVE。<br>试图通过指定提交一个特定地址范围MEM_COMMIT而不 MEM_RESERVE和非NULL lpAddress除非整个范围已经被预留失败。生成的错误代码为ERROR_INVALID_ADDRESS。<br>尝试提交已提交的页面不会导致该函数失败。这意味着您可以在不首先确定每个页面的当前承诺状态的情况下提交页面。<br>如果lpAddress指定安全区内的地址，则flAllocationType必须为MEM_COMMIT。|
|**MEM_RESERVE**<br>0x00002000|保留进程的一系列虚拟地址空间，而无需在内存或磁盘上的页面文件中分配任何实际的物理存储。<br>  您可以在后续调用VirtualAlloc函数时提交保留页面 。要一步保留和提交页面，请使用 MEM_COMMIT 调用VirtualAlloc MEM_RESERVE。<br>其他内存分配函数（如malloc和 LocalAlloc）在释放之前不能使用保留的内存范围。<br>|
|**MEM_RESET**<br>0x00080000|表示由lpAddress和 dwSize指定的内存范围中的数据不再受关注。不应从页面文件中读取或写入页面。但是，内存块将在以后再次使用，因此不应该将其解除。此值不能与任何其他值一起使用。<br>使用此值并不能保证使用MEM_RESET操作的范围 将包含零。如果您希望范围包含零，请退出内存然后重新发送。<br>指定MEM_RESET时， VirtualAlloc函数会忽略flProtect的值 。但是，您仍必须将flProtect设置为有效的保护值，例如PAGE_NOACCESS。<br>如果使用MEM_RESET并且内存范围映射到文件，VirtualAlloc将返回错误 。共享视图仅在映射到页面文件时才可接受。|
|**MEM_RESET_UNDO**<br>0x1000000|MEM_RESET_UNDO只应在哪个地址范围被称为 MEM_RESET成功之前应用。它表示由lpAddress和dwSize指定的指定内存范围内的数据 是调用者感兴趣的，并尝试反转MEM_RESET的影响。如果函数成功，则表示指定地址范围内的所有数据都是完整的。如果函数失败，则地址范围中的至少一些数据已被零替换。<br>此值不能与任何其他值一起使用。如果MEM_RESET_UNDO叫上没有地址范围MEM_RESET早些时候，该行为是不确定的。指定MEM_RESET时， VirtualAlloc函数会忽略flProtect的值 。但是，您仍必须将flProtect设置为有效的保护值，例如PAGE_NOACCESS。<br> **Windows Server 2008 R2，Windows 7，Windows Server 2008，Windows Vista，Windows Server 2003和Windows XP：  在Windows 8和Windows Server 2012之前不支持MEM_RESET_UNDO标志。**|
|**MEM_LARGE_PAGES**<br>0x20000000|使用大页面支持分配内存。<br>大小和对齐方式必须是大页面最小值的倍数。要获取此值，请使用 GetLargePageMinimum函数。<br>如果指定此值，则还必须指定**MEM_RESERVE和MEM_COMMIT**。|
|**MEM_PHYSICAL**<br>0x00400000|保留可用于映射Address Windowing Extensions（AWE）页面的地址范围 。<br>此值必须与MEM_RESERVE一起使用，不能与其他值一起使用。|
|**MEM_TOP_DOWN**<br>0x00100000|在尽可能高的地址分配内存。这可能比常规分配慢，尤其是在分配很多时。|
|**MEM_WRITE_WATCH**<br>0x00200000|使系统跟踪在分配的区域中写入的页面。如果指定此值，则还必须指定MEM_RESERVE。<br>要检索自分配区域或重置写入跟踪状态以来已写入的页面的地址，请调用 GetWriteWatch函数。要重置写入跟踪状态，请调用GetWriteWatch或 ResetWriteWatch。写入跟踪功能对内存区域保持启用状态，直到释放该区域为止|

**flProtect**  
要分配的页面区域的内存保护。如果正在提交页面，则可以指定任何一个 内存保护常量。  
如果lpAddress指定了安全区内的地址，则flProtect不能是以下任何值：  
    1. **PAGE_NOACCESS**  
    2. **PAGE_GUARD**  
    3. **PAGE_NOCACHE**  
    4. **PAGE_WRITECOMBINE**  

**返回值**  
如果函数成功，则返回值是分配的页面区域的基址。  
如果函数失败，则返回值为NULL。要获取扩展错误信息，请调用GetLastError。

**使用虚拟内存分配可执行内存代码如下：**  
```
#include <stdio.h>
#include <windows.h>

/* 定长指令集*/
#ifndef ASSEMBLY
#define ASSEMBLY

#define PUSH_EAX			0x50
#define PUSH_ECX			0x51
#define PUSH_EDX			0x52
#define PUSH_EBX			0x53
#define PUSH_ESP			0x54
#define PUSH_EBP			0x55
#define PUSH_ESI			0x56
#define PUSH_EDI			0x57
#define POP_EAX				0x58
#define POP_ECX				0x59
#define POP_EDX				0x5A
#define POP_EBX				0x5B
#define POP_ESP				0x5C
#define POP_EBP				0x5D
#define POP_ESI				0x5E
#define POP_EDI				0x5F
#define RET				0xC3
#define INT_3H				0xCC
#define NOP				0x90
#define PUSH(immi)			push immi

#endif // !ASSEMBLY

#define PAGE_SIZE 4096

#define PAGE_NUM(num)	num > 1 ? num * PAGE_SIZE : PAGE_SIZE

typedef int (*function)(int arg1, int arg2);

int main()
{
	int ires = 0xffffffff;
	unsigned char* CodeSegment = (unsigned char*)VirtualAlloc(NULL, PAGE_NUM(1), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (CodeSegment) {
		memset(CodeSegment, NOP, PAGE_SIZE);
		static unsigned char code[] = {
			0x55,					// push        ebp
			0x8B, 0xEC,				// mov         ebp,esp
			0x83, 0xEC, 0x04,			// sub         esp,4h
			0x8B, 0x45, 0x08,			// mov         eax,dword ptr[ebp + 8]
			0x03, 0x45, 0x0C,			// add         eax,dword ptr[ebp + 0Ch]
			0x89, 0x45, 0xFC,			// mov         dword ptr[ebp - 4],eax
			0x8B, 0x45, 0xFC,			// mov         eax,dword ptr[ebp - 4]
			0x8B, 0xE5,				// mov         esp, ebp
			0x5D,					// pop         ebp
			0xC3,					// ret
		};
		// 机器码存入虚拟内存
		memcpy(CodeSegment, code, sizeof(code));
		_asm {
			PUSH(2)
			PUSH(3)
			lea		edi, dword ptr[CodeSegment]
			call		[edi]
			add		esp, 8
			mov		[ires],	eax
			xor		eax, eax
		}
		printf("res=%d\n", ires);
		// 内存转换成函数指针
		function fun = (function)(CodeSegment);
		printf("fun=%d\n", fun(5, 10));
		// 释放分配的内存
		VirtualFree(CodeSegment, PAGE_SIZE, MEM_RELEASE);
	}
	else
	{
		printf("error\n");
	}
	return 0;
}

```
------------------------------------------------------------
[返回上级目录](./../../../../categories/Windows核心编程/README.md)  |
[返回首页](./../../../../README.md)