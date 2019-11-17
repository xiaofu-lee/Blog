#include <stdio.h>
#include <assert.h>
#include "Mutex.h"

int count = 0;

DWORD WINAPI ThreadProc1(LPVOID lpParam)
{
	Mutex* mutext = (Mutex*)lpParam;
	for (int i = 0; i < 100; i++)
	{
		mutext->lock();
		count++;
		printf("id = %5d, Count = %d\n", GetCurrentThreadId(), count);
		Sleep(80);
		mutext->unlock();
	}
	return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParam)
{
	Mutex* mutext = (Mutex*)lpParam;
	for (int i = 0; i < 100; i++)
	{
		mutext->lock();
		count++;
		printf("id = %5d, Count = %d\n", GetCurrentThreadId(), count);
		Sleep(80);
		mutext->unlock();
	}
	return 0;
}

int main(int argc, char* argv[])
{
	Mutex mutext(NULL);
	HANDLE hThread[2] = { 0 };
	hThread[0] = CreateThread(NULL, 0, ThreadProc1, &mutext, 0, NULL);
	// 创建一个挂起的线程
	hThread[1] = CreateThread(NULL, 0, ThreadProc2, &mutext, 0, NULL);
	// 等待所有线程执行结束
	WaitForMultipleObjects(2, hThread, true, INFINITE);
	printf("all thread execu over\n");

	/*
	OpenMutexA(
	_In_ DWORD dwDesiredAccess,
	_In_ BOOL bInheritHandle,
	_In_ LPCSTR lpName
	);
	dwDesiredAccess：对互斥量对象访问权限的设置，MUTEX_ALL_ACCESS 请求对互斥体的完全访问，
	MUTEX_MODIFY_STATE 允许使用 ReleaseMutex 函数，SYNCHRONIZE 允许互斥体对象同步使用；
	bInheritHandle：是否希望子进程继承互斥量对象的句柄，一般设置为false；
	lpName：要打开的互斥量对象的名称；
	*/
}