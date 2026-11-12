#ifndef CHAPTER03_Q03_STACK_QUEUE_API_H
#define CHAPTER03_Q03_STACK_QUEUE_API_H

#include <stdbool.h>

// 功能：声明第3章综合应用题03给出的栈和队列操作接口；原题只给抽象调用，具体存储与函数体仍由读者设计。
// 来源：《2027数据结构》第3章 3.3.5 综合应用题03；PDF第96页；书页第84页。
typedef struct Q03Stack Q03Stack;
typedef struct Q03Queue Q03Queue;

// 功能：将 value 压入栈；成功返回 true。
bool Push(Q03Stack *stack, int value);

// 功能：弹出栈顶并通过 value 输出；成功返回 true。
bool Pop(Q03Stack *stack, int *value);

// 功能：判断栈是否为空。
bool StackEmpty(const Q03Stack *stack);

// 功能：判断栈是否已满。
bool StackOverflow(const Q03Stack *stack);

// 功能：将 value 入队；成功返回 true。
bool Enqueue(Q03Queue *queue, int value);

// 功能：出队并通过 value 输出；成功返回 true。
bool Dequeue(Q03Queue *queue, int *value);

// 功能：判断队列是否为空。
bool QueueEmpty(const Q03Queue *queue);

#endif
