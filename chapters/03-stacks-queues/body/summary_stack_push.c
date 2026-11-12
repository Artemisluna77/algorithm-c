#include "summary_stack.h"
#include <stddef.h>

// 功能：先增加栈顶指针，再将元素放入新栈顶位置。
// 来源：《2027数据结构》第3章 归纳总结；PDF第120页；书页第108页。
bool SummaryPush(SummaryStack *stack, int value) {
    if (stack == NULL || stack->top < -1 ||
        stack->top >= SUMMARY_STACK_MAX_SIZE - 1) {
        return false;
    }
    stack->data[++stack->top] = value;
    return true;
}
