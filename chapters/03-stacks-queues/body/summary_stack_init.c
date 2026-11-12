#include "summary_stack.h"
#include <stddef.h>

// 功能：声明总结示例中的顺序栈并将栈顶指针初始化为 -1。
// 来源：《2027数据结构》第3章 归纳总结；PDF第120页；书页第108页。
void InitSummaryStack(SummaryStack *stack) {
    if (stack != NULL) {
        stack->top = -1;
    }
}
