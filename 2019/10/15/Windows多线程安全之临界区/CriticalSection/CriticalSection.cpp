#include "CriticalSection.h"

CriticalSection::CriticalSection()
{
	// 初始化临界区
	InitializeCriticalSection(&this->cs);
}

CriticalSection::~CriticalSection()
{
	this->destroy();
}

/*进入临界区*/
void CriticalSection::lock()
{
	EnterCriticalSection(&this->cs);
}

/*离开临界区*/
void CriticalSection::unlock()
{
	LeaveCriticalSection(&this->cs);
}

/*销毁临界区*/
void CriticalSection::destroy()
{
	DeleteCriticalSection(&this->cs);
}

CRITICAL_SECTION CriticalSection::getCriticalSection()
{
	return this->cs;
}