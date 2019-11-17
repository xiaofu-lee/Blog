<!--
{
	"author": "lxf",
	"title": "基于C语言的二叉搜索树的实现",
	"date": "2019-06-10 04:23:22",
	"category": "数据结构与算法"
}
-->

基于C语言的二叉搜索树的实现
------------------------------------------------------------
```
#include <stdio.h>
#include <stdlib.h>

#define TYPE int

typedef struct BSTreeNode
{
    TYPE key;
    struct BSTreeNode *parent; // 父节点
    struct BSTreeNode *left;   // 左孩子节点
    struct BSTreeNode *right;  // 右孩子节点
} Node, *BSTree;

// 创建节点
Node *createNode(TYPE key)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->parent = NULL;
    node->left = node->right = NULL;
    return node;
}

// 插入节点
void insertNode(BSTree *tree, Node *node)
{
    BSTree p = *tree;
    Node *parentNode = NULL;
    // 查找插入节点
    while (p)
    {
        parentNode = p;
        if (node->key < p->key)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }
    // 没有找到即根节点为空
    if (parentNode == NULL)
    {
        *tree = node;
        return;
    }
    if (node->key < parentNode->key)
    {
        // 插入左孩子
        parentNode->left = node;
    }
    else
    {
        // 插入右孩子
        parentNode->right = node;
    }
    node->parent = parentNode;
}

// 查找节点
Node *searchNode(BSTree tree, TYPE key)
{
    BSTree p = tree;
    while (p && p->key != key)
    {
        if (key < p->key)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }
    return p;
}

// 查找最小节点
Node *findMinNode(BSTree tree)
{
    BSTree p = tree;
    while (p->left != NULL)
    {
        p = p->left;
    }
    return p;
}

// 查找最大节点
Node *findMaxNode(BSTree tree)
{
    BSTree p = tree;
    while (p->right != NULL)
    {
        p = p->right;
    }
    return p;
}

// 删除节点
void deleteNode(BSTree *tree, TYPE key)
{
    BSTree p = *tree;
    Node *node = searchNode(p, key);
    // 节点不存在
    if (!node)
    {
        return;
    }
    // 待删除节点左右孩子为空
    if (!(node->left) && !(node->right))
    {
        // 是父节点
        if (node == *tree)
        {
            tree = NULL;
            free(p);
            return;
        }
        if (node == node->parent->left)
        {
            node->parent->left = NULL;
        }
        else
        {
            node->parent->right = NULL;
        }
        free(node);
    }
    // 左右孩子节点均不为空
    else if (node->left && node->right)
    {
        // 查找待删节点右子树最小节点
        Node *minNode = findMinNode(node->right);
        // 最小节点在父节点的左孩子
        if (minNode == minNode->parent->left)
        {
            // 清空父子节点的右子树
            minNode->parent->left = NULL;
        }
        else
        {
            // 清空父子节点的左子树
            minNode->parent->right = NULL;
        }
        // 继承待删除节点的父节点，及左右子树
        minNode->parent = node->parent;
        minNode->left = node->left;
        minNode->right = node->right;
        // 是父节点
        if (!(node->parent))
        {
            *tree = minNode;
        }
        else
        {
            if (node == node->parent->left)
            {
                node->parent->left = minNode;
            }
            else
            {
                node->parent->right = minNode;
            }
        }
        free(node);
    }
    else
    {
        // 待删除节点左右子树有一个为空
        // 保存孩子节点
        Node *childNode = (node->left) ? (node->left) : (node->right);
        // 待删节点是根节点
        if (!(node->parent))
        {
            childNode->parent = NULL;
            *tree = childNode;
        }
        else
        {
            childNode->parent = node->parent;
            if (node == node->parent->left)
            {
                node->parent->left = childNode;
            }
            else
            {
                node->parent->right = childNode;
            }
        }
        free(node);
    }
}

void destroyTree(BSTree *tree)
{
    if (tree == NULL)
    {
        return;
    }
    destroyTree(&((*tree)->left));
    destroyTree(&((*tree)->right));
    free((*tree));
}

//  先序遍历
void DLR(BSTree tree)
{
    if (tree == NULL)
    {
        return;
    }
    printf("%d  ", tree->key);
    DLR(tree->left);
    DLR(tree->right);
}

// 中序遍历
void LDR(BSTree tree)
{
    if (tree == NULL)
    {
        return;
    }
    LDR(tree->left);
    printf("%d  ", tree->key);
    LDR(tree->right);
}

// 后序遍历
void LRD(BSTree tree)
{
    if (tree == NULL)
    {
        return;
    }
    LRD(tree->left);
    LRD(tree->right);
    printf("%d  ", tree->key);
}

int main(int argc, char const *argv[])
{
    BSTree tree = NULL;
    TYPE value[8] = {10, 20, 30, 40, 5, 25, 15, 5};
    Node *node = NULL;
    for (int i = 0; i < 8; i++)
    {
        node = createNode(value[i]);
        insertNode(&tree, node);
    }
    DLR(tree);
    printf("\n");
    LRD(tree);
    printf("\n");
    LDR(tree);
    printf("\n");

    deleteNode(&tree, 30);

    node = createNode(35);
    insertNode(&tree, node);

    LDR(tree);
    printf("\n");

    destroyTree(&tree);

    return 0;
}
```
------------------------------------------------------------
[返回上级目录](./../../../../categories/数据结构与算法/README.md)  |
[返回首页](./../../../../README.md)