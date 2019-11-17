#include "Mutex.h"

Mutex::Mutex(char* lpName):lpName(lpName)
{
	// bInitialOwner第二个参数用来确定互斥量的初始拥有者。
	this->hMutex = CreateMutexA(NULL, false, this->lpName);
}

Mutex::~Mutex()
{
	this->destroy();
}

const char& Mutex::getName()
{
	return *(this->lpName);
}

// 进入临界区
int Mutex::lock()
{
	// INFINITE，表示阻塞等待
	return WaitForSingleObject(this->hMutex, INFINITE);
}

// 释放临界区
bool Mutex::unlock()
{
	return ReleaseMutex(this->hMutex);
}

bool Mutex::destroy()
{
	return CloseHandle(this->hMutex);
}
