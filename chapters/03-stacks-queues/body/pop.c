#include "sequential_stack.h"
#include <stddef.h>

// 功能：检查顺序栈非空后读取栈顶元素，并将栈顶指针减 1。
// 来源：《2027数据结构》第3章 3.1.2；PDF第77页；书页第65页。
bool Pop(SequentialStack *stack, int *value) {
    if (stack == NULL || value == NULL || stack->top < 0 ||
        stack->top >= SEQUENTIAL_STACK_MAX_SIZE) {
        return false;
    }
    *value = stack->data[stack->top--];
    return true;
}
