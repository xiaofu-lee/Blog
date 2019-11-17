#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#include <windows.h>
class Semaphores
{
public:
	Semaphores(const char* lpName, long lInitialCount = 1,long lMaximumCount = 1);
	virtual ~Semaphores();
	int lock();
	bool unlock();
	bool destroy();

private:
	HANDLE hSemaphore;
	long lMaximumCount;
};

#endif