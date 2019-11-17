<!--
{
	"author": "lxf",
	"title": "Leecode-删除链表的倒数第N个节点",
	"date": "2019-09-22 11:49:54",
	"category": "数据结构与算法"
}
-->

Leecode-删除链表的倒数第N个节点
------------------------------------------------------------
问题描述：
给定一个链表，删除链表的倒数第?n?个节点，并且返回链表的头结点。

示例：

给定一个链表: 1->2->3->4->5, 和 n = 2.

当删除了倒数第二个节点后，链表变为 1->2->3->5.
说明：

给定的 n?保证是有效的。

来源：力扣（LeetCode）链接：https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list

代码：
```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode* p = head;
    struct ListNode* tmp;
    int size = 0;
    
    while(p){
        size++;
        p = p->next;
    }
    
    if(size == n ) {
        head = head->next;
        return head;
    }
    
    if(size == 2) {
        if(n == 1) {
            free(head->next);
            head->next = NULL;
            return head;
        }
    }
    
    p = head;
    
    while(size - n > 1)
    {
        p = p->next;
        size--;
    }
    tmp = p->next;
    p->next = tmp->next;
    free(tmp);
    return head;
}
```
------------------------------------------------------------
[返回上级目录](./../../../../categories/数据结构与算法/README.md)  |
[返回首页](./../../../../README.md)