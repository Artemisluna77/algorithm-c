#ifndef CHAPTER05_BINARY_TREE_H
#define CHAPTER05_BINARY_TREE_H

#include <stddef.h>

// 功能：定义带左、右孩子指针的二叉链表结点。
// 来源：《2027数据结构》第5章 5.2.2；PDF第144页；书页第132页。
typedef struct BinaryNode {
    int data;
    struct BinaryNode *left;
    struct BinaryNode *right;
} BinaryNode;

typedef struct IntArray {
    int *data;
    size_t length;
    int ok;
} IntArray;

#define INT_ARRAY_INIT {NULL, 0, 0}

typedef enum TraversalOrder {
    Preorder,
    Inorder,
    Postorder
} TraversalOrder;

// 功能：以前序次序访问二叉树的根、左子树和右子树。
// 来源：《2027数据结构》第5章 5.3.1；PDF第153页；书页第141页。
IntArray PreOrder(const BinaryNode *root);

// 功能：以中序次序访问二叉树的左子树、根和右子树。
// 来源：《2027数据结构》第5章 5.3.1；PDF第153页；书页第141页。
IntArray InOrder(const BinaryNode *root);

// 功能：以后序次序访问二叉树的左子树、右子树和根。
// 来源：《2027数据结构》第5章 5.3.1；PDF第153页；书页第141页。
IntArray PostOrder(const BinaryNode *root);

// 功能：使用队列按层访问二叉树结点。
// 来源：《2027数据结构》第5章 5.3.1；PDF第154页；书页第142页。
IntArray LevelOrder(const BinaryNode *root);

// 功能：释放遍历结果数组并清空字段。
void IntArrayDestroy(IntArray *array);

typedef void (*VisitFunction)(int value, void *context);

// 功能：按先序、中序或后序的访问位置递归遍历二叉树。
// 来源：依据《2027数据结构》第5章归纳总结中的 Track 模板补入访问回调；PDF第204–205页；书页第192–193页。
void Track(const BinaryNode *root, TraversalOrder order,
           VisitFunction visit, void *context);

#endif
