#include "Event.h"

Event::Event(const char* lpName, bool bInitialState, bool bManualReset)
{
	/*
	CreateEventA(
	_In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,
	_In_ BOOL bManualReset,
	_In_ BOOL bInitialState,
	_In_opt_ LPCSTR lpName
	);
	参数说明
	第一个参数表示安全控制，一般直接传入NULL。
	第二个参数确定事件是手动置位还是自动置位，传入TRUE表示手动置位，传入FALSE表示自动置位。如果为自动置位，则对该事件调用WaitForSingleObject()后会自动调用ResetEvent()使事件变成未触发状态。
	第三个参数表示事件的初始状态，传入TRUR表示已触发。
	第四个参数表示事件的名称，传入NULL表示匿名事件。
	*/
	this->hEvent = CreateEvent(NULL, bManualReset, bInitialState, lpName);
}
Event::~Event()
{
	this->destroy();
}

bool Event::destroy()
{
	return CloseHandle(this->hEvent);
}

// 默认是阻塞等待
int Event::wait(int dwMilliseconds)
{
	return WaitForSingleObject(this->hEvent, dwMilliseconds);
}

/*激活状态*/
bool Event::notify(HANDLE houtEvent)
{
	return SetEvent(houtEvent);
}

/*未激活状态*/
bool Event::reset()
{
	return ResetEvent(this->hEvent);
}

HANDLE Event::getEvent()
{
	return this->hEvent;
}