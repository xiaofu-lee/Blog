#include <stdio.h>
#include <assert.h>
#include "Event.h"

#define MAX 100

int apple = 0;
Event proEvent(NULL, true, true);
Event consumeEvent(NULL, false, true);

// 生产者线程函数
DWORD WINAPI Product(LPVOID lpParam)
{
	while (1) {
		proEvent.wait();
		if (apple >= MAX) {
			proEvent.notify(consumeEvent.getEvent());
			proEvent.reset();
		}
		else {
			apple++;
			printf("Product id = %5d, Count = %d\n", GetCurrentThreadId(), apple);
		}
		Sleep(60);
	}
	return 0;
}

// 消费者线程函数
DWORD WINAPI ConsumerPro(LPVOID lpParam)
{
	while (true) {
		consumeEvent.wait();
		if (apple == 0) {
			consumeEvent.notify(proEvent.getEvent());
			consumeEvent.reset();
		}
		else {
			apple--;
			printf("id = %5d, Count = %d\n", GetCurrentThreadId(), apple);
		}
		Sleep(60);
	}
}


int main(int argc, char* argv[])
{
	HANDLE hThread[2] = { 0 };
	hThread[0] = CreateThread(NULL, 0, Product, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, ConsumerPro, NULL, 0, NULL);
	// 等待所有线程执行结束
	WaitForMultipleObjects(2, hThread, true, INFINITE);
	printf("all thread execu over\n");
}