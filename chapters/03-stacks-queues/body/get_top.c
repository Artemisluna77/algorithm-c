#include "sequential_stack.h"
#include <stddef.h>

// 功能：读取顺序栈栈顶元素但保持栈状态不变。
// 来源：《2027数据结构》第3章 3.1.2；PDF第78页；书页第66页。
bool GetTop(const SequentialStack *stack, int *value) {
    if (stack == NULL || value == NULL || stack->top < 0 ||
        stack->top >= SEQUENTIAL_STACK_MAX_SIZE) {
        return false;
    }
    *value = stack->data[stack->top];
    return true;
}
