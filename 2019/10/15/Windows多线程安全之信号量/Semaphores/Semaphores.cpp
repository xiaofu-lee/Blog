#include "Semaphores.h"

Semaphores::Semaphores(const char* lpName, long lInitialCount, long lMaximumCount):lMaximumCount(lMaximumCount)
{
	this->hSemaphore = CreateSemaphore(NULL, lInitialCount, lMaximumCount, lpName);
}

Semaphores::~Semaphores()
{
	this->destroy();
}

int Semaphores::lock()
{
	return WaitForSingleObject(this->hSemaphore, INFINITE);
}
bool Semaphores::unlock()
{
	return ReleaseSemaphore(this->hSemaphore, 1, NULL);
}
bool Semaphores::destroy()
{
	return CloseHandle(this->hSemaphore);
}