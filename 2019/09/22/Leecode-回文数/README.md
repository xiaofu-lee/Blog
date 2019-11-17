<!--
{
	"author": "lxf",
	"title": "Leecode-回文数",
	"date": "2019-09-22 11:45:26",
	"category": "数据结构与算法"
}
-->

Leecode-回文数
------------------------------------------------------------
问题描述：
判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。

示例 1:
```
输入: 121
输出: true
```
示例 2:
```
输入: -121
输出: false
解释: 从左向右读, 为 -121 。 从右向左读, 为 121- 。因此它不是一个回文数。
```
示例 3:
```
输入: 10
输出: false
解释: 从右向左读, 为 01 。因此它不是一个回文数。
```

来源：力扣（LeetCode）链接：https://leetcode-cn.com/problems/palindrome-number

代码：
```
bool isPalindrome(int x){
    if (x < 0) {
        return false;
    }
    int num[20] = {0};
    int i = 0;
    while (x > 0) {
        num[i++] = x % 10;
        x /= 10;
    }
    for(int j=0; j<i/2; j++) {
        if (num[j] != num[i-j-1]) {
            return false;
        }
    }
    return true;
}
```
------------------------------------------------------------
[返回上级目录](./../../../../categories/数据结构与算法/README.md)  |
[返回首页](./../../../../README.md)