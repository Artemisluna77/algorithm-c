#ifndef CHAPTER02_ANSWER_Q17_NODE_H
#define CHAPTER02_ANSWER_Q17_NODE_H

typedef int Q17ElemType;

// 功能：定义第17题倒数第 k 个结点算法使用的 link 域结点及带头结点链表类型。
// 来源：《2027数据结构》第2章习题答案第17题；PDF第71页；书页第59页。
typedef struct Q17Node {
    Q17ElemType data;
    struct Q17Node *link;
} Q17Node;

typedef Q17Node *Q17LinkList;

#endif
