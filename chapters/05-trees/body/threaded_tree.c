#include "threaded_tree.h"

#include <stdint.h>
#include <stdlib.h>

// 功能：递归建立中序前驱和后继线索。
// 来源：《2027数据结构》第5章 5.3.2；PDF第156–157页；书页第144–145页。
void InThread(ThreadNode *node, ThreadNode **predecessor) {
    if (node == NULL || predecessor == NULL) {
        return;
    }
    if (node->leftTag == 0) {
        InThread(node->left, predecessor);
    }
    if (node->left == NULL) {
        node->leftTag = 1;
        node->left = *predecessor;
    }
    if (*predecessor != NULL && (*predecessor)->right == NULL) {
        (*predecessor)->rightTag = 1;
        (*predecessor)->right = node;
    }
    *predecessor = node;
    if (node->rightTag == 0) {
        InThread(node->right, predecessor);
    }
}

// 功能：建立整棵二叉树的中序线索，并为空的末结点右域标记线索。
// 来源：《2027数据结构》第5章 5.3.2；PDF第157页；书页第145页。
void CreateInThread(ThreadNode *root) {
    ThreadNode *predecessor = NULL;
    InThread(root, &predecessor);
    if (predecessor != NULL && predecessor->right == NULL) {
        predecessor->rightTag = 1;
        predecessor->right = NULL;
    }
}

// 功能：沿左孩子指针找到中序第一个结点。
// 来源：《2027数据结构》第5章 5.3.2；PDF第157页；书页第145页。
ThreadNode *FirstNode(ThreadNode *node) {
    if (node == NULL) {
        return NULL;
    }
    while (node->leftTag == 0 && node->left != NULL) {
        node = node->left;
    }
    return node;
}

// 功能：通过右子树最左结点或右线索取得中序后继。
// 来源：《2027数据结构》第5章 5.3.2；PDF第157页；书页第145页。
ThreadNode *NextNode(ThreadNode *node) {
    if (node == NULL) {
        return NULL;
    }
    if (node->rightTag == 0) {
        return FirstNode(node->right);
    }
    return node->right;
}

// 功能：沿线索链非递归收集中序遍历序列。
// 来源：《2027数据结构》第5章 5.3.2；PDF第158页；书页第146页。
char *ThreadedInOrder(ThreadNode *root) {
    size_t length = 0;
    size_t capacity = 0;
    char *values = NULL;
    ThreadNode *node;
    for (node = FirstNode(root); node != NULL; node = NextNode(node)) {
        char *new_values;
        size_t new_capacity;
        if (length == SIZE_MAX - 1) {
            free(values);
            return NULL;
        }
        if (length + 1 >= capacity) {
            new_capacity = capacity == 0 ? 8 : capacity * 2;
            if (new_capacity <= capacity) {
                free(values);
                return NULL;
            }
            new_values = (char *)realloc(values, new_capacity);
            if (new_values == NULL) {
                free(values);
                return NULL;
            }
            values = new_values;
            capacity = new_capacity;
        }
        values[length++] = node->data;
    }
    if (values == NULL) {
        values = (char *)malloc(1);
        if (values == NULL) {
            return NULL;
        }
    }
    values[length] = '\0';
    return values;
}
