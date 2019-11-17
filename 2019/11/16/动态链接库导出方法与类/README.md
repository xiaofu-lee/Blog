<!--
{
	"author": "lxf",
	"title": "动态链接库导出方法与类",
	"date": "2019-11-16 14:31:03",
	"category": "Windows核心编程"
}
-->

动态链接库导出方法与类
------------------------------------------------------------
2019-11-16 14:31:03 &emsp;   

#### 一、导出C函数  

```
头文件
#define C_DLL_EXPORT_API extern "C" __declspec(dllexport)

C_DLL_EXPORT_API int __cdecl add(int arg1, int arg2);
C_DLL_EXPORT_API void __cdecl say(void);

源码文件
#include <cstdio>

int add(int arg1, int arg2)
{
	return arg1 + arg2;
}

void say(void)
{
	printf("导出C函数\n");
}
```

#### 二、导出C++函数

```
头文件
#define CPP_DLL_EXPORT_API __declspec(dllexport)

CPP_DLL_EXPORT_API int add(int arg1, int arg2);
CPP_DLL_EXPORT_API void say(void);

源码文件
#include <cstdio>

int add(int arg1, int arg2)
{
	return arg1 + arg2;
}

void say(void)
{
	printf("导出C++函数\n");
}
```

#### 三、导出C++类

```
头文件
#define CPP_CLASS_DLL_EXPORT_API __declspec(dllexport)

class CPP_CLASS_DLL_EXPORT_API  CStudent
{
public:
	CStudent(int num, int grade);
	~CStudent();
	void PrintInfo();

private:
	int num;
	int grade;
};

源码文件
#include <cstdio>

CStudent::CStudent(int num, int grade) :num(num), grade(grade)
{
}

CStudent::~CStudent()
{
}

void CStudent::PrintInfo()
{
	printf("num = %d, grade = %d\n", num, grade);
}
入口函数
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
```
#### 四、DLL函数导出重命名解决方案

1. 使用 `extern "C"`

2. 使用 `#pragma comment(linker, "/export:[Exports Name]=[Mangling Name]") `
   `eg: #pragma comment(linker, "/export:name=_name@num")`

1. 使用def文件自定义

#### 五、DLL调用方式

1. 隐式调用

   使用#pragma comment(lib, “XX.lib”)的方式，或直接将XX.lib加入到工程中。 
   
2. 显式调用

    使用LoadLibrary载入动态链接库、使用GetProcAddress获取某函数地址。 
    
3. 使用def文件自定义

#### 六、查看DLL导出函数方法

1. 使用  [**Dependency Walker**]( http://www.dependencywalker.com/ ) 工具查看

2. 使用VS自带的 **dumpbin **查看

   打开Visual Studio 命令提示符 

   输入盘符 eg F:， 使用cd  指令进入DLL所在的文件夹

   输入指令**dumpbin  -exports  DllName.dll**
   输入指令**dumpbin   /LINKERMEMBER   DllLibName.lib**查看静态库信息
   
   

参考资料

[1] [HowTo: Export C++ classes from a DLL](https://www.codeproject.com/Articles/28969/HowTo-Export-C-classes-from-a-DLL)

------------------------------------------------------------
[返回上级目录](./../../../../categories/Windows核心编程/README.md)  |  [返回首页](./../../../../README.md)