#ifndef CHAPTER02_ANSWER_Q19_NODE_H
#define CHAPTER02_ANSWER_Q19_NODE_H

// 功能：定义第19题去重算法使用的带 link 指针单链表结点。
// 来源：《2027数据结构》第2章习题答案第19题；PDF第73页；书页第61页。
typedef struct Q19Node {
    int data;
    struct Q19Node *link;
} Q19Node;

#endif
