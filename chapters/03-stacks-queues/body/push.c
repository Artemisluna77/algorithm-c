#include "sequential_stack.h"
#include <stddef.h>

// 功能：检查顺序栈未满后先移动栈顶指针，再将元素写入栈顶。
// 来源：《2027数据结构》第3章 3.1.2；PDF第77页；书页第65页。
bool Push(SequentialStack *stack, int value) {
    if (stack == NULL || stack->top < -1 ||
        stack->top >= SEQUENTIAL_STACK_MAX_SIZE - 1) {
        return false;
    }
    stack->data[++stack->top] = value;
    return true;
}
