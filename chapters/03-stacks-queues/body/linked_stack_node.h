#ifndef CH03_LINKED_STACK_NODE_H
#define CH03_LINKED_STACK_NODE_H

// 功能：定义链式栈结点，next 指向下一个结点；结点所有权由链表使用者管理。
// 来源：《2027数据结构》第3章 3.1.3；PDF第78页；书页第66页。
typedef struct LinkStackNode {
    int data;
    struct LinkStackNode *next;
} LinkStackNode;

#endif
