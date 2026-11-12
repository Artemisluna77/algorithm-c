#include "summary_stack.h"
#include <stddef.h>

// 功能：读取当前栈顶元素，再将 top 减 1。
// 来源：《2027数据结构》第3章 归纳总结；PDF第120页；书页第108页。
bool SummaryPop(SummaryStack *stack, int *value) {
    if (stack == NULL || value == NULL || stack->top < 0 ||
        stack->top >= SUMMARY_STACK_MAX_SIZE) {
        return false;
    }
    *value = stack->data[stack->top--];
    return true;
}
