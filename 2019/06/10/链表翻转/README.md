<!--
{
	"author": "lxf",
	"title": "链表翻转",
	"date": "2019-06-10 04:26:33",
	"category": "数据结构与算法"
}
-->

链表翻转
------------------------------------------------------------
**难度：简单**  
**题目描述：**  
反转一个单链表。  
实例：  
  ```
  输入: 1->2->3->4->5->NULL
  输出: 5->4->3->2->1->NULL
  ```

**解题思路：头插法**

**源码如下**
```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head) {
    if(!head) return head;
    struct ListNode* p = head->next;
    struct ListNode* tmp = NULL;
    struct ListNode* newHead = head;
    newHead->next = NULL;
    
    while(p) {
        tmp = p->next;
        p->next = newHead;
        newHead = p;
        p = tmp;
    }
    return newHead;
}
```
------------------------------------------------------------
[返回上级目录](./../../../../categories/数据结构与算法/README.md)  |
[返回首页](./../../../../README.md)