<!--
{
	"author": "lxf",
	"title": "常用排序算法锦集",
	"date": "2019-06-10 11:31:02",
	"category": "数据结构与算法"
}
-->

常用排序算法锦集
------------------------------------------------------------
1. 快速排序  
基本思想：  
1．先从数列中取出一个数作为基准数。  
2．分区过程，将比这个数大的数全放到它的右边，小于或等于它的数全放到它的左边。  
3．再对左右区间重复第二步，直到各区间只有一个数。  
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATA_TYPE int
#define MAX 50

void swap(DATA_TYPE *a, DATA_TYPE *b);

// 划分
int Partition(DATA_TYPE *array, int start, int end)
{
    int reference = array[start]; // 参考基准数
    int i = start;
    int j = end;
    while (i != j)
    {
        while (array[j] >= reference && i < j)
        {
            j--;
        }
        while (array[i] <= reference && i < j)
        {
            i++;
        }
        if (i < j)
        {
            //交换两个数在数组中的位置
            swap(array + i, array + j);
        }
    }
    // while (i != j)
    // {
    //     if (array[j] >= reference)
    //     {
    //         j--;
    //     }
    //     else
    //     {
    //         //交换两个数在数组中的位置
    //         swap(array + i, array + j);
    //         i++;
    //     }
    // }
    swap(array + start, array + i);
    return i;
}

// 随机划分
int RandomPartition(DATA_TYPE *array, int start, int end)
{
    int reference = rand() % (end - start) + start + 1;
    swap(array + start, array + reference);
    return Partition(array, start, end);
}

void QuickSort(DATA_TYPE *array, int length, int start, int end)
{
    if (start < end)
    {
        int split = RandomPartition(array, start, end);
        QuickSort(array, length, start, split - 1);
        QuickSort(array, length, split + 1, end);
    }
}

void swap(DATA_TYPE *a, DATA_TYPE *b)
{
    if (*a != *b)
    {
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}

/**
 * 初始化数据
*/
void InitData(DATA_TYPE* array, int len)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < len; i++)
    {
        array[i] = rand() % MAX;
    }
}

/**
 * 输出数据
*/
void PrintArray(const DATA_TYPE* array, int len)
{
    printf("[");
    for (int i = 0; i < len; i++)
    {
        printf("%2d ", array[i]);
    }
    printf("]\n");
}

int main(int argc, char *argv[])
{
    int len = 20;
    DATA_TYPE* array = new DATA_TYPE[len];
    InitData(array, len);
    PrintArray(array, len);
    QuickSort(array, len, 0, len - 1);
    PrintArray(array, len);
    return 0;
}
```
2. 冒泡排序
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATA_TYPE int
#define MAX 50

void swap(DATA_TYPE *a, DATA_TYPE *b);

/**
 * 冒泡排序
*/
void BubbleSort(DATA_TYPE* array, int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (array[j] > array[j + 1]) {
                swap(array + j, array + j + 1);
            }
        }
    }
}

/**
 * 双向冒泡排序
*/
void BothwayBubbleSort(DATA_TYPE* array, int len)
{
    for (int i = 0; i < ((len - 1) / 2) ; i++)
    {
        for (int j = i; j < (len - i - 1); j++)
        {
            if (array[j] > array[j + 1]) {
                swap(array + j, array + j + 1);
            }
            if (array[len - i - 1 - j] < array[len - i - 1 - j - 1]) {
                swap(array + (len - i - 1 - j - 1), array + (len - i - 1 - j));
            }
        }
    }
}

void swap(DATA_TYPE *a, DATA_TYPE *b)
{
    if (*a != *b)
    {
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}

/**
 * 初始化数据
*/
void InitData(DATA_TYPE* array, int len)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < len; i++)
    {
        array[i] = rand() % MAX;
    }
}

/**
 * 输出数据
*/
void PrintArray(const DATA_TYPE* array, int len)
{
    printf("[");
    for (int i = 0; i < len; i++)
    {
        printf("%2d ", array[i]);
    }
    printf("]\n");
}

int main(int argc, char *argv[])
{
    int len = 20;
    DATA_TYPE* array = new DATA_TYPE[len];
    InitData(array, len);
    PrintArray(array, len);
    // BubbleSort(array, len);
    BothwayBubbleSort(array, len);
    PrintArray(array, len);
    return 0;
}
```
3. 选择排序
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATA_TYPE int
#define MAX 50

/**
 * 选择排序
*/
void SelectionSort(DATA_TYPE* array, int len)
{
    int max_index = 0;
    for (int i = 0; i < len; i++)
    {
        if (array[i] > array[max_index])
        {
            max_index = i;
        }
    }
    if (max_index != len - 1) {
        // 找到最大的放到最后
        DATA_TYPE max = array[max_index];
        array[max_index] = array[len - 1];
        array[len - 1] = max;
    }

    if (len > 1)
    {
        SelectionSort(array, len - 1);
    }
}

/**
 * 初始化数据
*/
void InitData(DATA_TYPE* array, int len)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < len; i++)
    {
        array[i] = rand() % MAX;
    }
}

/**
 * 输出数据
*/
void PrintArray(const DATA_TYPE* array, int len)
{
    printf("[");
    for (int i = 0; i < len; i++)
    {
        printf("%2d ", array[i]);
    }
    printf("]\n");
}

int main(int argc, char *argv[])
{
    int len = 20;
    DATA_TYPE* array = new DATA_TYPE[len];
    InitData(array, len);
    PrintArray(array, len);
    SelectionSort(array, len);
    PrintArray(array, len);
    return 0;
}
```
4. 插入排序
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATA_TYPE int
#define MAX 50

void swap(DATA_TYPE *a, DATA_TYPE *b);

/**
 * 插入排序
*/
void InsertSort(DATA_TYPE *array, int length)
{
    for (int i = 1; i < length; i++)
    {
        int j = i;
        while (array[j] < array[j - 1] && j > 0)
        {
            swap(array + j, array + j - 1);
            j--;
        }
    }
}

void swap(DATA_TYPE *a, DATA_TYPE *b)
{
    if (*a != *b)
    {
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}

/**
 * 初始化数据
*/
void InitData(DATA_TYPE *array, int len)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < len; i++)
    {
        array[i] = rand() % MAX;
    }
}

/**
 * 输出数据
*/
void PrintArray(const DATA_TYPE *array, int len)
{
    printf("[");
    for (int i = 0; i < len; i++)
    {
        printf("%2d ", array[i]);
    }
    printf("]\n");
}

int main(int argc, char *argv[])
{
    int len = 20;
    DATA_TYPE *array = new DATA_TYPE[len];
    InitData(array, len);
    PrintArray(array, len);
    InsertSort(array, len);
    PrintArray(array, len);
    return 0;
}
```
5. 归并排序
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATA_TYPE int
#define MAX 50

void merge(DATA_TYPE *array, int left, int mid, int right)
{
	int i = left;
	int j = mid + 1;
	int k = 0;
	int temp[256] = { 0 };
	while (i <= mid && j <= right)
	{
		if (array[i] <= array[j])
		{
			temp[k++] = array[i++];
		}
		else
		{
			temp[k++] = array[j++];
		}
	}
	while (i <= mid)
	{
		temp[k++] = array[i++];
	}
	while (j <= right)
	{
		temp[k++] = array[j++];
	}
	for (i = 0; i < k; i++)
	{
		array[left + i] = temp[i];
	}
}

void divide(DATA_TYPE *array, int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		if (left < mid)
		{
			divide(array, left, mid);
		}
		if (mid + 1 < right)
		{
			divide(array, mid + 1, right);
		}
		merge(array, left, mid, right);
	}
}

/**
* 归并排序
*/
void MergeSort(DATA_TYPE *array, int length)
{
	if (length > 0 && array != NULL)
	{
		divide(array, 0, length - 1);
	}
}

/**
* 初始化数据
*/
void InitData(DATA_TYPE *array, int len)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < len; i++)
	{
		array[i] = rand() % MAX;
	}
}

/**
* 输出数据
*/
void PrintArray(const DATA_TYPE *array, int len)
{
	printf("[");
	for (int i = 0; i < len; i++)
	{
		printf("%2d ", array[i]);
	}
	printf("]\n");
}

int main(int argc, char *argv[])
{
	int len = 20;
	DATA_TYPE *array = new DATA_TYPE[len];
	InitData(array, len);
	PrintArray(array, len);
	MergeSort(array, len);
	PrintArray(array, len);
	getchar();
	return 0;
}
```
6. 希尔排序
------------------------------------------------------------
[返回上级目录](./../../../../categories/数据结构与算法/README.md)  |
[返回首页](./../../../../README.md)