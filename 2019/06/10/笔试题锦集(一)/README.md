<!--
{
	"author": "lxf",
	"title": "笔试题锦集(一)",
	"date": "2019-06-10 11:30:00",
	"category": "数据结构与算法"
}
-->

笔试题锦集(一)
------------------------------------------------------------
1. 一个由英文单词和空格组成的字符串，其中的字母大小写皆有。现需要对字符串格式化输出，要求（1）每个单词首字母大写，其余字母小写；（2）单词之间仅保留一个空格。请编程实现。   
```
[例子]
输入：“tHe      qUIcK     BrOwn fox JUmPs    oVEr tHE     laZy  DOG”
输出：“The Quick Brown Fox Jumps Over The Lazy Dog”
```
代码实现：
```
#include <stdio.h>
#include <string.h>

// 大写转小写
char tolower(char ch)
{
    if (ch >= 65 && ch <= 90)
    {
        return (ch + 32);
    } else {
        return ch;
    }
}

// 小写转大写
char toupper(char ch)
{
    if (ch >= 97 && ch <= 122)
    {
        return (ch - 32);
    } else {
        return ch;
    }
}

int fun(const char *pstr, unsigned int strlen, char *pOutStr, unsigned int outStrlen)
{
    int len = 0;
    int word = 0;
    for(int i = 0; i < strlen; i++)
    {
        if (pstr[i] != ' ')
        {
            pOutStr[len++] = tolower(pstr[i]);
            word++;
            // 采用向后看一位的预测分析法
            if(pstr[i + 1] == ' ') {
                pOutStr[len - word] = toupper(pOutStr[len - word]);
                pOutStr[len++] = ' ';
                word = 0;
            }
            if ((i + 1) == strlen) {
                pOutStr[len - word] = toupper(pOutStr[len - word]);
                word = 0;
            }
        }
    }
    return len;
}

int main(int argc, char *argv[])
{
    char in[256] = {0x00};
    char out[256] = {0x00};
    printf("请输入字符串：");
    char ch;
    int count = 0;
    do
    {
        scanf("%c", &ch);
        in[count++] = ch;
    } while (ch != '\n');

    // gets_s(str, 256);
    fun(in, count, out, count);
    puts(out);
    return 0;
}
```

2. 用数组记录最近N天广州的气温，若连续几天气温持续升高称为一次升温，求最近N天内升温的最大温差。
```
[例子]输入温度数组[21, 28, 26, 29, 31, 28, 29]，输出最大温差31-26=5。
```
代码实现：
```
#include <stdio.h>

int calcMaximumTemperature(const int* temperature, unsigned int len)
{
    int continuous_count = 0;
    int max_continuous_count = -1;
    int cur_index = 0;
    for (unsigned int i = 0; i < len - 1; i++)
    {
        if (temperature[i] < temperature[i + 1]) {
            continuous_count++;
        } else {
            if (continuous_count > max_continuous_count) {
				max_continuous_count = continuous_count;
				cur_index = i;
			}
            continuous_count = 0;
        }
    }
    return (temperature[cur_index] - temperature[cur_index - max_continuous_count]);
}

int main(int argc, char* argv[])
{
	int N = 0;
	printf("请输入天数：");
    scanf("%d", &N);
	int* array = new int[N] { 0 };
	int j = N;
	while (j)
	{
		printf("请输入气温：");
        scanf("%d", array + (N - j) );
		j--;
	}
	int result = calcMaximumTemperature(array, N);
	printf("%d\n", result);
	return 0;
}
```

3. 一份数据以链表的形式存储，链表的每个元素都为整数，且由小到大依次排列，请编程删除这个链表中的重复数据。  
```
[例子]
输入：2 -> 2 -> 2 -> 3 -> 3 -> 6 -> 12 -> 15 -> 15
输出：2 -> 3 -> 6 -> 12 -> 15
```
代码实现：
```
#include <stdio.h>
#include <stdlib.h>

typedef struct _LinkNode {
	int value;
	struct _LinkNode* next;
}LinkNode, *pLinkNode;

/**
 * 创建新节点
*/
LinkNode* CreateNode(int value) {
	LinkNode* pnode = (LinkNode*)malloc(sizeof(LinkNode));
	pnode->value = value;
	pnode->next = NULL;
	return pnode;
}

/**
 * 头插法
*/
bool frontInsertNode(pLinkNode *linkList, pLinkNode pNode) {
	LinkNode* head = *linkList;
	if (head) {
		pNode->next = head->next;
		head->next = pNode;
		return true;
	}
	return false;
}

/**
 * 尾插发
*/
bool rearInsertNode(pLinkNode *linkList, pLinkNode pNode) {
	LinkNode* head = *linkList;
    if (head) {
        LinkNode* p = head;
        while (p->next) {
            p = p->next;
        }
        p->next = pNode;
        return true; 
    }
	return false;
}

/**
 * 移除重复元素
*/
bool removeDuplication(pLinkNode *linkList) {
	LinkNode* head = *linkList;
	if (head) {
        LinkNode* p = head;
		while (p->next) {
			if ( !(p->value ^ p->next->value) ) {
				LinkNode* temp = p->next;
				p->next = p->next->next;
				free(temp);
				temp = NULL;
			}
			else {
				p = p->next;
			}
		}
		return true;
	}
	return false;
}

/**
 * 输出链表元素
*/
void printfLinklist(pLinkNode linkList)
{
	LinkNode* head = linkList;
	if (head) {
		LinkNode* p = head;
		while (p->next) {
			printf("%d->", p->next->value);
			p = p->next;
		}
		printf("\n");
	}
}

int main(int argc, char* argv[])
{
	pLinkNode linkList = CreateNode(0);
	int count = 0;
	int num = 0;
	printf("请输入元素个数：");
    scanf("%d", &count);
	while (count) {
		printf("请输入元素：");
        scanf("%d", &num);
		LinkNode* node =  CreateNode(num);
		rearInsertNode(&linkList, node);
        count--;
	}
	printfLinklist(linkList);
	removeDuplication(&linkList);
	printfLinklist(linkList);
	return 0;
}

```

4. 某游戏设计有一个PVP活动，每场比赛胜出会获得积分并累计。活动结束后需要根据总积分高低进行排名。当两个角色积分相同时，则需额外以角色战力进行排序，战力高的排在前面。请编程输出获得此次比赛第5名的选手。  
代码实现：
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 50
#define DATA_TYPE int

typedef struct _Role{
    int id;
    DATA_TYPE integral; // 积分
    DATA_TYPE combat_effectiveness; // 战斗力
} Role;

/**
 * 通过战斗力交换
*/
void swapByCombat(Role *arg1, Role *arg2)
{
    if (arg1->combat_effectiveness < arg2->combat_effectiveness)
    {
        Role temp = *arg1;
        *arg1 = *arg2;
        *arg2 = temp;
    }
}

/**
 * 通过积分交换
*/
void swapByIntegral(Role *arg1, Role *arg2)
{
    if (arg1->integral != arg2->integral)
    {
        Role temp = *arg1;
        *arg1 = *arg2;
        *arg2 = temp;
    }
}

/**
 * 冒泡排序
*/
void bubbleSort(Role *array, int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (array[j].integral < array[j + 1].integral) {
                swapByIntegral(array + j, array + j + 1);
            }
            else if (array[j].integral == array[j + 1].integral) {
                swapByCombat(array + j, array + j + 1);
            }
        }
    }
}

/**
 * 双向冒泡排序
*/
void bothwayBubbleSort(Role *array, int len)
{
    for (int i = 0; i < (len - 1) / 2 ; i++)
    {
        for (int j = i; j < (len - i - 1); j++)
        {
            if (array[j].integral < array[j + 1].integral) {
                swapByIntegral(array + j, array + j + 1);
            }
            if (array[j].integral == array[j + 1].integral) {
                swapByCombat(array + j, array + j + 1);
            }

            if (array[len - i - 1 - j].integral > array[len - i - 1 - j - 1].integral) {
                swapByIntegral(array + (len - i - 1 - j), array + (len - i - 1 - j - 1));
            }
            if (array[len - i - 1 - j].integral == array[len - i - 1 - j - 1].integral) {
                swapByCombat(array + (len - i - 1 - j - 1), array + (len - i - 1 - j));
            }
        }
    }
}

void printArray(Role array[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("id = %2d 的积分为：%2d, 战斗力为：%2d\n", array[i].id, array[i].integral, array[i].combat_effectiveness);
    }
    printf("-------------------------------------------------------------------------\n");
}

void initdata(Role array[], int len)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < len; i++)
    {
        Role mRole;
        mRole.id = i + 1;
        mRole.integral =  rand() % MAX;
        mRole.combat_effectiveness = rand() % MAX;
        array[i] =  mRole;
    }
}


int main(int argc, char *argv[])
{
    int len = 20;
    Role* array = new Role[len];
    initdata(array, len);
    printArray(array, len);
    // bubbleSort(array, len);
    bothwayBubbleSort(array, len);
    printArray(array, len);
    return 0;
}
```

5. 手机号码由11个连续的阿拉伯数字组成，请编程找出输入字符串中的手机号码，并在其两端加上\<phone>\</phone>标签。

```
[例子]
输入：“我的手机是13688888888，我家住在xxxxxxxx。”
输出：“我的手机是<phone>13688888888</phone>，我家住在xxxxxxxx。”
```
代码实现：
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char inBuffer[255] = "我的手机是13688888888，我家住在xxxxxxxx。";
    char outBuffer[255] = {0x00};
    char ch;
    int count = strlen(inBuffer);
    // do {
    //     scanf("%c", ch);
    //     inBuffer[count++] = count;
    // } while (ch != '\n');

    int num_count = 0;
    int j = 0;
    for (int i = 0; i < count; i++)
    {
        if (inBuffer[i] >= '0' && inBuffer[i] <= '9')
        {
            num_count++;
        } else {
            if (num_count == 11) {
                if (inBuffer[i - num_count] == '1') {
                    memcpy(outBuffer + j, &"<phone>", 7);
                    j += 7;
                    memcpy(outBuffer + j, inBuffer + i - num_count, num_count);
                    j += 11;
                    memcpy(outBuffer + j, &"</phone>", 8);
                    j += 8;
                }
            }
            num_count = 0;
            outBuffer[j++] = inBuffer[i];
        }
    }
    puts(outBuffer);
	return 0;
}
```

6. 编程将A、B两个链表拼接在一起，链表的每个元素都为整数，如果A链表的结尾和B链表的开头一样，只保留一份。  
```
[例子]
输入：1 -> 3 -> 5 -> 7  和  3 -> 5 -> 7 -> 9
输出：1 -> 3 -> 5 -> 7 -> 9
```
代码实现：
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _LinkNode {
	int value;
	struct _LinkNode* next;
}LinkNode, *pLinkNode;

/**
 * 创建新节点
*/
LinkNode* CreateNode(int value) {
	LinkNode* pnode = (LinkNode*)malloc(sizeof(LinkNode));
	pnode->value = value;
	pnode->next = NULL;
	return pnode;
}

/**
 * 头插法
*/
bool frontInsertNode(pLinkNode *linkList, pLinkNode pNode) {
	LinkNode* head = *linkList;
	if (head) {
		pNode->next = head->next;
		head->next = pNode;
		return true;
	}
	return false;
}

/**
 * 尾插发
*/
bool rearInsertNode(pLinkNode *linkList, pLinkNode pNode) {
	LinkNode* head = *linkList;
    if (head) {
        LinkNode* p = head;
        while (p->next) {
            p = p->next;
        }
        p->next = pNode;
        return true; 
    }
	return false;
}

/**
 * 移除重复元素
*/
bool removeDuplication(pLinkNode *linkList) {
	LinkNode* head = *linkList;
	if (head) {
        LinkNode* p = head;
		while (p->next) {
			if ( !(p->value ^ p->next->value) ) {
				LinkNode* temp = p->next;
				p->next = p->next->next;
				free(temp);
				temp = NULL;
			}
			else {
				p = p->next;
			}
		}
		return true;
	}
	return false;
}

/**
 * 拼接链表
*/
bool JointLinkList(pLinkNode *linkListA, pLinkNode linkListB) {
	LinkNode* headA = *linkListA;
    LinkNode* headB = linkListB;
	if (headA && headB) {
        LinkNode* pA = headA->next;
        LinkNode* pB = headB->next;
        LinkNode* ptempa = headA;
		while (pA) {
            if (pB && pB->value == pA->value) {
                pB = pB->next;
            } else {
                pB = headB->next;
            }
            ptempa = pA;
            pA = pA->next;
		}
        ptempa->next = pB;
        return true;
	}
	return false;
}

/**
 * 输出链表元素
*/
void printfLinklist(pLinkNode linkList)
{
	LinkNode* head = linkList;
	if (head) {
		LinkNode* p = head;
		while (p->next) {
			printf("%d->", p->next->value);
			p = p->next;
		}
		printf("\n");
	}
}

int main(int argc, char* argv[])
{
	pLinkNode linkListA = CreateNode(0);
    pLinkNode linkListB = CreateNode(0);
	int count = 0;
	int num = 0;
	printf("请输入元素个数：");
    scanf("%d", &count);
	while (count) {
		printf("请输入元素：");
        scanf("%d", &num);
		LinkNode* nodea =  CreateNode(num);
		rearInsertNode(&linkListA, nodea);
        printf("请输入元素：");
        scanf("%d", &num);
        LinkNode* nodeb =  CreateNode(num);
		rearInsertNode(&linkListB, nodeb);
        count--;
	}
	printfLinklist(linkListA);
	printfLinklist(linkListB);
    JointLinkList(&linkListA, linkListB);
    printfLinklist(linkListA);
	return 0;
}
```

7. 某蛋糕店推出一种礼品卡，使用该卡可以用于购买店内的蛋糕，每种蛋糕限购1个。
   该卡片面值为R元，仅可以使用1次，结账后卡内剩下的余额作废。
   已知店内的全部种类的蛋糕价格都为整数，求出怎么购买，可使结账后卡内剩下的余额最少。  
代码实现：
```
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char* argv[])
{
    int R = 21;
    int price[] = {4, 3, 11, 13, 9};
    int category = sizeof(price) / sizeof(int);

    int** dp = new int*[category + 1]{nullptr};

    for (size_t i = 0; i <= category; i++)
    {
        dp[i] = new int[R + 1]{0};
    }
    

    for (size_t i = 1; i < category; i++)
    {
        for (size_t j = 1; j <= R; j++)
        {
            if(j >= price[i - 1])
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - price[i - 1]] + price[i - 1]);
            }
            else 
            {
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    for (size_t i = 1; i < category; i++)
    {
        for (size_t j = 1; j <= R; j++)
        {
            printf("%2d ,", dp[i][j]);
        }
        printf("\n");
    }
	return 0;
}
```

1. 同时投掷N颗色子，将投掷得到数字之和记为S，编程输出S可能的取值及相应的概率。  
代码实现：
```

```
------------------------------------------------------------
[返回上级目录](./../../../../categories/数据结构与算法/README.md)  |
[返回首页](./../../../../README.md)