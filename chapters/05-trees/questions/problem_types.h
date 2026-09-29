#ifndef CHAPTER05_PROBLEM_TYPES_H
#define CHAPTER05_PROBLEM_TYPES_H

#include <stddef.h>

// 功能：定义表达式树的运算符/操作数结点，作为综合题输入结构。
// 来源：《2027数据结构》第5章 5.3.3 试题16；PDF第163页；书页第151页。
typedef struct ExpressionNode {
    char data[10];
    struct ExpressionNode *left;
    struct ExpressionNode *right;
} ExpressionNode;

#define SEQUENTIAL_TREE_MAX_SIZE 128
#define SEQUENTIAL_TREE_EMPTY_NODE (-1)

// 功能：定义顺序存储二叉树题目的结点数组和实际占用长度；结点值为正整数，空位使用 SEQUENTIAL_TREE_EMPTY_NODE（-1）。
// 来源：《2027数据结构》第5章 5.3.3 试题17；PDF第164页；书页第152页。
typedef struct SequentialTree {
    int nodes[SEQUENTIAL_TREE_MAX_SIZE];
    size_t elementCount;
} SequentialTree;

#endif
