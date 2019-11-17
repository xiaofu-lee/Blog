<!--
{
	"author": "lxf",
	"title": "常见位运算操作",
	"date": "2019-04-11 03:30:31",
	"category": "C语言程序设计"
}
-->

常见位运算操作
------------------------------------------------------------
```
/**
 * 获取低N位
 **/
#define LowByte(var, n) ( var & ( (1 << n) - 1))

/**
 * 获取高N位
 **/
#define HighByte(var, n) (\
    ( var >> ( ( sizeof(var) << 3 ) - n ) ) & ( (1 << n) - 1 ) )

/**
 * 标志位处理
 * 取var的第positionigh bit位
 * 现将var算数右移position -1位
 * 后与1按位与
 * */
#define getBit(var, position)(\
        ( var >> (position -1) ) & 1 )

/**
 * 标志位处理
 * 取var的第position bit位设置为0或者1
 * */
char setBit(char var, int position, int value) {
    value &= 1;
    if (value) {
        return var | (1 << (position -1));
    } else {
        return var & ( ~( 1 << (position -1) ) );
    }
}

// 将GB2312转为数字
int StrToInt(const unsigned char *cpstr)
{
    for(int i = 0; cpstr[i] != 0x00; i++)
    {
        if (cpstr[i] & 0x80) {
            return cpstr[i] << 8 + cpstr[i + 1];
        } else {
            return cpstr[i]
        }
    }
}
```

算数运算
```
#include <stdio.h>

int add(int arg1, int arg2);
int sub(int arg1, int arg2);
int mul(int arg1, int arg2);
int div(int arg1, int arg2);

/**
 * 加法器
 * desc:使用亦或实现加法，使用按位与实现进位检查
 */ 
int add(int arg1, int arg2)
{
    int x = arg1 ^ arg2;
    int carry = arg1 & arg2;
    while(carry) {
        carry <<= 1;
        arg1 = x;
        arg2 = carry;
        x = arg1 ^ arg2;
        carry = arg1 & arg2;
    }
    return x;
}

/**
 * 减法器
 * desc:减去一个数等于加上一个负数
 */ 
int sub(int arg1, int arg2)
{
    return add(arg1, mul(arg2, 0xFFFFFFFF));
}

/**
 * 乘法器
 * desc:x * y 可表示为 x 个 y 相加
 */ 
int mul(int arg1, int arg2)
{
    int sum = arg2;
    while(arg1 > 1) {
        sum = add(sum, arg2);
        arg1 = sub(arg1, 1);
    }
    return sum;
}

/**
 * 除法器
 * desc:x - y 可表示为x减去几个y=0
 */ 
int div(int arg1, int arg2)
{
    int sum = 0;
    while(arg1) {
        arg1 = sub(arg1, arg2);
        sum = add(sum, 1);
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    int res = add(100, -50);
    printf("res = %d\n", res);

    res = sub(100, 10);
    printf("res = %d\n", res);

    res = mul(3, 9);
    printf("res = %d\n", res);

    res = div(9, 3);
    printf("res = %d\n", res);
    return 0;
}

```
------------------------------------------------------------
[返回上级目录](./../../../../categories/C语言程序设计/README.md)  |
[返回首页](./../../../../README.md)