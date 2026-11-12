#ifndef CHAPTER02_ANSWER_Q18_NODE_H
#define CHAPTER02_ANSWER_Q18_NODE_H

// 功能：定义第18题共享单词后缀算法使用的字符型单链表结点。
// 来源：《2027数据结构》第2章习题答案第18题；PDF第72页；书页第60页。
typedef struct Q18Node {
    char data;
    struct Q18Node *next;
} Q18Node;

#endif
