#include "shared_stack.h"
#include <stddef.h>

// 功能：从指定共享栈弹出栈顶元素，并按对应方向移动栈顶指针。
// 来源：《2027数据结构》第3章 3.1.4 综合应用题05答案；PDF第87–88页；书页第75–76页。
bool SharedPop(SharedStack *stacks, int stack_number, int *value) {
    if (stacks == NULL || value == NULL) {
        return false;
    }
    if (stack_number == 0) {
        if (stacks->top[0] < 0 ||
            stacks->top[0] >= SHARED_STACK_MAX_SIZE ||
            stacks->top[1] < 0 || stacks->top[1] > SHARED_STACK_MAX_SIZE ||
            stacks->top[0] >= stacks->top[1]) {
            return false;
        }
        *value = stacks->data[stacks->top[0]--];
        return true;
    }
    if (stack_number == 1) {
        if (stacks->top[1] <= 0 ||
            stacks->top[1] >= SHARED_STACK_MAX_SIZE ||
            stacks->top[0] < -1 || stacks->top[0] >= stacks->top[1]) {
            return false;
        }
        *value = stacks->data[stacks->top[1]++];
        return true;
    }
    return false;
}
