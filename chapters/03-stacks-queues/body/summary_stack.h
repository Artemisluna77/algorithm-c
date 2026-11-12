#ifndef CH03_SUMMARY_STACK_H
#define CH03_SUMMARY_STACK_H

#include <stdbool.h>

#define SUMMARY_STACK_MAX_SIZE 50

// 功能：声明总结示例使用的顺序栈数组，并将初始 top 设为 -1。
// 来源：《2027数据结构》第3章 归纳总结；PDF第120页；书页第108页。
typedef struct {
    int data[SUMMARY_STACK_MAX_SIZE];
    int top;
} SummaryStack;

// 功能：将总结示例中的顺序栈 top 初始化为 -1。
// 来源：《2027数据结构》第3章 归纳总结；PDF第120页；书页第108页。
void InitSummaryStack(SummaryStack *stack);

// 功能：用 stack[++top]=x 的方式将元素压入总结示例中的顺序栈。
// 来源：《2027数据结构》第3章 归纳总结；PDF第120页；书页第108页。
bool SummaryPush(SummaryStack *stack, int value);

// 功能：用 x=stack[top--] 的方式弹出栈顶元素；空栈或参数无效时返回 false。
// 来源：《2027数据结构》第3章 归纳总结；PDF第120页；书页第108页。
bool SummaryPop(SummaryStack *stack, int *value);

#endif
