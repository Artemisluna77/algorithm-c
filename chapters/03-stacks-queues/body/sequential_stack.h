#ifndef CH03_SEQUENTIAL_STACK_H
#define CH03_SEQUENTIAL_STACK_H

#include <stdbool.h>

#define SEQUENTIAL_STACK_MAX_SIZE 50

typedef struct {
    int data[SEQUENTIAL_STACK_MAX_SIZE];
    int top;
} SequentialStack;

// 功能：将顺序栈初始化为空栈，栈顶指针设为 -1。
// 来源：《2027数据结构》第3章 3.1.2；PDF第77页；书页第65页。
void InitStack(SequentialStack *stack);

// 功能：判断顺序栈是否为空。
// 来源：《2027数据结构》第3章 3.1.2；PDF第77页；书页第65页。
bool StackEmpty(const SequentialStack *stack);

// 功能：将元素压入顺序栈，栈满或结构无效时返回 false。
// 来源：《2027数据结构》第3章 3.1.2；PDF第77页；书页第65页。
bool Push(SequentialStack *stack, int value);

// 功能：弹出顺序栈顶元素并写入 value，空栈或参数无效时返回 false。
// 来源：《2027数据结构》第3章 3.1.2；PDF第77页；书页第65页。
bool Pop(SequentialStack *stack, int *value);

// 功能：读取顺序栈顶元素但不出栈，空栈或参数无效时返回 false。
// 来源：《2027数据结构》第3章 3.1.2；PDF第78页；书页第66页。
bool GetTop(const SequentialStack *stack, int *value);

#endif
