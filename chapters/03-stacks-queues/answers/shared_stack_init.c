#include "shared_stack.h"
#include <stddef.h>

// 功能：将 0 号栈顶置于 -1，1 号栈顶置于数组容量处。
// 来源：《2027数据结构》第3章 3.1.4 综合应用题05答案；PDF第87页；书页第75页。
void InitSharedStack(SharedStack *stacks) {
    if (stacks != NULL) {
        stacks->top[0] = -1;
        stacks->top[1] = SHARED_STACK_MAX_SIZE;
    }
}
