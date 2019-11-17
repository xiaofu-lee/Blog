<!--
{
	"author": "lxf",
	"title": "Linux系统编程之多线程锁与条件变量",
	"date": "2019-08-14 02:57:21",
	"category": "Linux系统编程"
}
-->

Linux系统编程之多线程锁与条件变量
------------------------------------------------------------
### 1. 互斥量（pthread_mutex_t）  
```

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//初始互斥量  
pthread_mutex_init(&lock, NULL);

// 加锁
pthread_mutex_lock(&lock);

// 尝试加锁非阻塞
pthread_mutex_trylock(&lock);

// 加锁超时 等待直到锁可用，或者超时
struct timespec tnsec;
tnsec.tv_nsec = 5000000;
tnsec.tv_sec = 30;
pthread_mutex_timedlock(&lock, &tnsec);

// 释放锁
pthread_mutex_unlock(&lock);

//销毁化互斥量
pthread_mutex_destroy(&lock);
```

### 2. 读写锁（pthread_rwlock_t）  
```
// 初始化读写锁
int pthread_rwlock_init(pthread_rwlock_t* restrict rwlock, const pthread_rwlockattr_t* restrict attr);

// 加读锁
int pthread_rwlock_rdlock(pthread_rwlock_t* rwlock);

// 尝试加读锁占用则返回失败
int pthread_rwlock_tryrdlock(pthread_rwlock_t* rwlock);

// 加写锁
int pthread_rwlock_wrlock(pthread_rwlock_t* rwlock);

// 尝试加写锁占用则返回失败
int pthread_rwlock_trywrlock(pthread_rwlock_t* rwlock);

// 释放读写锁
int pthread_rwlock_unlock(pthread_rwlock_t* rwlock);

// 销毁读写锁
int pthread_rwlock_destroy(pthread_rwlock_t* rwlock);

```

### 3. 自旋锁（pthread_spinlock_t）  
```
pshared的取值及其含义：
PTHREAD_PROCESS_SHARED：该自旋锁可以在多个进程中的线程之间共享。
PTHREAD_PROCESS_PRIVATE：仅初始化本自旋锁的线程所在的进程内的线程才能够使用该自旋锁。
// 初始化自旋锁
int pthread_spin_init(pthread_spinlock_t* lock, int pshared);

// 加自旋锁
int pthread_spin_lock(pthread_spinlock_t* lock);

// 尝试加自旋锁 占用则返回失败
int pthread_spin_trylock(pthread_spinlock_t* lock);

// 释放自旋锁
int pthread_spin_unlock(pthread_spinlock_t* lock);

// 销毁自旋锁
int pthread_spin_destroy(pthread_spinlock_t* lock);
```

### 3. 条件变量（pthread_cond_t）  
```
// 初始化条件变量
int pthread_cond_init (pthread_cond_t *__restrict __cond, const pthread_condattr_t *__restrict __cond_attr);
// 等待一个条件变量
int pthread_cond_wait (pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex);
// 唤醒其中一个等待该条件变量的线程
int pthread_cond_signal (pthread_cond_t *__cond);
// 唤醒所有等待该条件变量的线程
int pthread_cond_broadcast (pthread_cond_t *__cond);
// 销毁条件变量
int pthread_cond_destroy (pthread_cond_t *__cond);


#include <cstdio>
#include <unistd.h>
#include <pthread.h>
#include<cassert>
#include <string.h>
#include <time.h>

pthread_mutex_t lock;
pthread_cond_t cond;

int apple = 0;

void* consumer_pro(void* arg)
{
	while (1)
	{
		pthread_mutex_lock(&lock);
		while (apple == 0)
		{
			pthread_cond_wait(&cond, &lock);
		}
		apple--;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

void* producer_pro(void* arg)
{
	while (1)
	{
		pthread_mutex_lock(&lock);
		apple++;
		pthread_cond_signal(&cond);
		//pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}


int main()
{
	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&lock, NULL);

	pthread_t thread1, thread2;
	int iret1 = pthread_create(&thread1, NULL, consumer_pro, NULL);
	assert(iret1 == 0);
	int iret2 = pthread_create(&thread2, NULL, producer_pro, NULL);
	assert(iret2 == 0);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	//销毁化互斥量
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);
	getchar();
    return 0;
}
```
------------------------------------------------------------
[返回上级目录](./../../../../categories/Linux系统编程/README.md)  |
[返回首页](./../../../../README.md)