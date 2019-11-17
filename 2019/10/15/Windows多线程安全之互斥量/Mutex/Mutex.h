#ifndef MUTEX_H
#define MUTEX_H

#include <windows.h>

class Mutex
{
public:
	Mutex(char* lpName);
	virtual ~Mutex();

	const char& getName();

	int lock();
	bool unlock();
	bool destroy();

private:
	HANDLE hMutex;
	char* lpName;
};

#endif