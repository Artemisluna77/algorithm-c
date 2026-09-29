#include "sequential_stack.h"
#include <stddef.h>

// 功能：初始化顺序栈为空栈，将栈顶指针设为 -1。
// 来源：《2027数据结构》第3章 3.1.2；PDF第77页；书页第65页。
void InitStack(SequentialStack *stack) {
    if (stack != NULL) {
        stack->top = -1;
    }
}
