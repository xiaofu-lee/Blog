<!--
{
	"author": "lxf",
	"title": "Leecode-和最大子数组",
	"date": "2019-09-22 11:40:43",
	"category": "数据结构与算法"
}
-->

Leecode-和最大子数组
------------------------------------------------------------
题目描述：
给定一个整数数组，找到一个具有最大和的子数组，返回其最大和。  
实例：
```
[-2,2,-3,4,-1,2,1,-5,3],符合要求的子数组为[4,-1,2,1],最大和为6
```
代码：
```
#include<stdio.h>

int main(int argc, char const *argv[])
{
    int array[] = {-2,2,-3,4,-1,2,1,-5,3};
    int len = sizeof(array) / sizeof(int);
    int max = 0x80000000;
    int start = 0;
    int end = 0;
    for (int i = 0; i < len; i++)
    {
        int sum = 0;
        for (int j = i; j < len; j++)
        {
            sum += array[j];
            if (sum > max) {
                max = sum;
                start = i;
                end = j;
            }
        }
    }
    for (size_t i = start; i <= end; i++)
    {
        printf("%d, ", array[i]);
    }
    
    printf("max = %d\n", max);
    return 0;
}


贪心解法
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int array[] = {-2, 2, -3, 4, -1, 2, 1, -5, 3};
    int len = sizeof(array) / sizeof(int);
    int max = 0x80000000;
    int start = 0;
    int end = 0;
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum += array[i];
        if (sum > max)
        {
            max = sum;
            end = i;
        }
        if (sum < 0)
        {
            sum = 0;
            start = i + 1;
        }
    }
    for (size_t i = start; i <= end; i++)
    {
        printf("%d, ", array[i]);
    }
    printf("max = %d\n", max);
    return 0;
}

```
------------------------------------------------------------
[返回上级目录](./../../../../categories/数据结构与算法/README.md)  |
[返回首页](./../../../../README.md)