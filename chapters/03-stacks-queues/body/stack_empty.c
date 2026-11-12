#include "sequential_stack.h"
#include <stddef.h>

// 功能：当栈顶指针为 -1 时判定顺序栈为空。
// 来源：《2027数据结构》第3章 3.1.2；PDF第77页；书页第65页。
bool StackEmpty(const SequentialStack *stack) {
    return stack == NULL || stack->top < 0 || stack->top >= SEQUENTIAL_STACK_MAX_SIZE;
}
