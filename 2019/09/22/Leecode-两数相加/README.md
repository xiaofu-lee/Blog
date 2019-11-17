<!--
{
	"author": "lxf",
	"title": "Leecode-两数相加",
	"date": "2019-09-22 11:48:08",
	"category": "数据结构与算法"
}
-->

Leecode-两数相加
------------------------------------------------------------
问题描述：
给出两个?非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照?逆序?的方式存储的，并且它们的每个节点只能存储?一位?数字。

如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

您可以假设除了数字 0 之外，这两个数都不会以 0?开头。

示例：
```
输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807
```
来源：力扣（LeetCode）链接：https://leetcode-cn.com/problems/add-two-numbers

代码：
```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* createNode(int val) {
    struct ListNode* node = (struct ListNode*) malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int carry = 0;
    int sum = 0;
    struct ListNode* head = NULL;
    struct ListNode* point = NULL;
    struct ListNode* temp = NULL;
    
    while(l1 || l2) {
        sum = 0;
        if (l1 ) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2 ) {
            sum += l2->val;
            l2 = l2->next;
        }
        sum += carry;
        carry = sum / 10;
        sum %= 10;
        if (head == NULL) {
            head = createNode(sum);
            point = head;
        } else {
            temp = createNode(sum);
            point->next = temp;
            point = point->next;
        }
    }  
    if (carry) {
        temp = createNode(carry);
        point->next = temp;
    }
    return head;
}
```
------------------------------------------------------------
[返回上级目录](./../../../../categories/数据结构与算法/README.md)  |
[返回首页](./../../../../README.md)