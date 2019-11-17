#ifndef CRITICAL_SECTION_H
#define CRITICAL_SECTION_H

#include <windows.h>

class CriticalSection
{
public:
	CriticalSection();
	virtual ~CriticalSection();

	void lock();
	void unlock();
	void destroy();

	CRITICAL_SECTION getCriticalSection();

private:
	CRITICAL_SECTION cs;
};

#endif





