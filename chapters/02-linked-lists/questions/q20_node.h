#ifndef CHAPTER02_QUESTION20_NODE_H
#define CHAPTER02_QUESTION20_NODE_H

// 功能：保留题目 20 中给出的单链表结点数据类型。
// 来源：《2027数据结构》第2章 2.3.7 题20；PDF第57页；书页第45页。
typedef struct Question20Node {
    int data;
    struct Question20Node *next;
} Question20Node;

#endif
