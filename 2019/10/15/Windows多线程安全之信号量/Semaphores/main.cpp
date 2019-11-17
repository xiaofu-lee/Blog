#include <stdio.h>
#include <assert.h>
#include "Semaphores.h"

int count = 0;

DWORD WINAPI ThreadProc1(LPVOID lpParam)
{
	Semaphores* semaphores = (Semaphores*)lpParam;
	for (int i = 0; i < 100; i++)
	{
		semaphores->lock();
		count++;
		printf("id = %5d, Count = %d\n", GetCurrentThreadId(), count);
		Sleep(80);
		semaphores->unlock();
	}
	return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParam)
{
	Semaphores* semaphores = (Semaphores*)lpParam;
	for (int i = 0; i < 100; i++)
	{
		semaphores->lock();
		count++;
		printf("id = %5d, Count = %d\n", GetCurrentThreadId(), count);
		Sleep(80);
		semaphores->unlock();
	}
	return 0;
}

DWORD WINAPI ThreadProc3(LPVOID lpParam)
{
	Semaphores* semaphores = (Semaphores*)lpParam;
	for (int i = 0; i < 100; i++)
	{
		semaphores->lock();
		count++;
		printf("id = %5d, Count = %d\n", GetCurrentThreadId(), count);
		Sleep(80);
		semaphores->unlock();
	}
	return 0;
}

int main(int argc, char* argv[])
{
	Semaphores semaphores(NULL, 3, 3);
	HANDLE hThread[3] = { 0 };
	hThread[0] = CreateThread(NULL, 0, ThreadProc1, &semaphores, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, ThreadProc2, &semaphores, 0, NULL);
	hThread[2] = CreateThread(NULL, 0, ThreadProc3, &semaphores, 0, NULL);
	// 等待所有线程执行结束
	WaitForMultipleObjects(3, hThread, true, INFINITE);
	printf("all thread execu over\n");

	/*
	OpenSemaphoreA(
    _In_ DWORD dwDesiredAccess,
    _In_ BOOL bInheritHandle,
    _In_ LPCSTR lpName
    );
	dwDesiredAccess：对互斥量对象访问权限的设置，SEMAPHORE_ALL_ACCESS 请求对互斥体的完全访问，
	SEMAPHORE_MODIFY_STATE 允许使用 ReleaseSemaphore 函数，SYNCHRONIZE 允许互斥体对象同步使用；
	bInheritHandle：是否希望子进程继承互斥量对象的句柄，一般设置为false；
	lpName：要打开的互斥量对象的名称；
	*/
}