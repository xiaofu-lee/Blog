#ifndef _EVENT_H_
#define _EVENT_H_

#ifndef _WINDOWS_
#include <windows.h>
#endif

class Event
{
public:
	Event(const char* lpName, bool bInitialState, bool bManualReset = true);
	virtual ~Event();
	int wait(int dwMilliseconds = INFINITE);
	bool notify(HANDLE houtEvent);
	bool destroy();
	bool reset();
	HANDLE getEvent();
private:
	HANDLE hEvent;
};

#endif
