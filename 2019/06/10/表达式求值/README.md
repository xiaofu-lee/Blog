<!--
{
	"author": "lxf",
	"title": "表达式求值",
	"date": "2019-06-10 04:20:06",
	"category": "数据结构与算法"
}
-->

表达式求值
------------------------------------------------------------
源代码
```
#include <stack>
#include <stdio.h>

#define MAX 0x7FFFFFFF
#define MIN 0xFFFFFFFF

using namespace std;

// 操作数栈
stack<int> sOPND;
// 操作符栈
stack<char> sOPTR;

// 操作符集合表
char OPTR[] = {'+', '-', '*', '/', '(', ')', '#', '\0'};

// 操作符优先级表
char PrecedeR[][7] = {
    //+    -    *    /    (    )    #
    {'>', '>', '<', '<', '<', '>', '>'},  // +
    {'>', '>', '<', '<', '<', '>', '>'},  // -
    {'>', '>', '>', '>', '<', '>', '>'},  // *
    {'>', '>', '>', '>', '<', '>', '>'},  // /
    {'<', '<', '<', '<', '<', '=', ' '},  // (
    {'>', '>', '>', '>', ' ', '>', '>'},  // )
    {'<', '<', '<', '<', '<', ' ', '='}}; // #

// 判断是否在操作符集合 返回所在集合索引
int IsInOP(char op)
{
    int i;
    for (i = 0; OPTR[i] != '\0'; ++i)
    {
        if (op == OPTR[i])
        {
            // 返回索引
            return i;
        }
    }
    return MIN;
}

// 判断两个操作符的优先级
char Precede(char ch1, char ch2)
{
    if (IsInOP(ch1) != -1 && IsInOP(ch2) != -1)
    {
        return PrecedeR[IsInOP(ch1)][IsInOP(ch2)];
    }
    return ' ';
}

// 判断是否是操作数
int IsDigit(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return 1;
    }
    return 0;
}

// 执行运算操作
int Operate(char theta, int a, int b)
{
    switch (theta)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        return MAX;
    }
}

int calculator(const char *str)
{
    int position = 0, num = 0;
    sOPTR.push('#');
    while (str[position] != '#' || sOPTR.top() != '#')
    {
        char ch = str[position];
        if (IsDigit(ch))
        {
            num = num * 10 + (ch - '0');
            position++;
        }
        else
        {
            if (num != 0)
            {
                // 是操作数则进操作数栈
                sOPND.push(num);
                // 清零
                num = 0;
            }
            switch (Precede(sOPTR.top(), ch))
            {
            case '<':
                // 期待符优先级高于操作符栈顶元素则期待符入栈，读头指向下一个期待符
                sOPTR.push(ch);
                position++;
                break;
            case '>':
            {
                // 期待符优先级低于操作符栈顶元素则操作符栈顶元素出栈
                // 操作数栈弹出两个操作数 进行相应的算数符号运算并将运算结果压入操作数栈
                int b = sOPND.top();
                sOPND.pop();
                int a = sOPND.top();
                sOPND.pop();
                sOPND.push(Operate(sOPTR.top(), a, b));
                sOPTR.pop();
                break;
            }
            case '=':
                // 期待符优先级等于操作符栈顶元素则操作符栈顶元素出栈，读头指向下一个期待符
                sOPTR.pop();
                position++;
                break;
            }
        }
    }
    if (!sOPTR.empty())
    {
        return sOPND.top();
    }
    return MAX;
}

int main(int argc, char const *argv[])
{
    char str[80];
    while (1)
    {
        printf("请输入算数表达式\n");
        gets(str);
        sprintf(str, "%s%c", str, '#');
        int result = calculator(str);
        printf("计算结果:%d\n", result);
    }
    return 0;
}

```
------------------------------------------------------------
[返回上级目录](./../../../../categories/数据结构与算法/README.md)  |
[返回首页](./../../../../README.md)