#include "shared_stack.h"
#include <stddef.h>

// 功能：根据栈号分别向上或向下压栈，并在两个栈顶相邻时拒绝操作。
// 来源：《2027数据结构》第3章 3.1.4 综合应用题05答案；PDF第87页；书页第75页。
bool SharedPush(SharedStack *stacks, int stack_number, int value) {
    if (stacks == NULL || (stack_number != 0 && stack_number != 1) ||
        stacks->top[0] < -1 || stacks->top[0] >= SHARED_STACK_MAX_SIZE ||
        stacks->top[1] < 0 || stacks->top[1] > SHARED_STACK_MAX_SIZE ||
        stacks->top[1] - stacks->top[0] <= 1) {
        return false;
    }
    if (stack_number == 0) {
        stacks->data[++stacks->top[0]] = value;
    } else {
        stacks->data[--stacks->top[1]] = value;
    }
    return true;
}
