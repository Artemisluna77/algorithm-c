#include "stack_algorithms.h"

#include <stdlib.h>

// 功能：借助栈将连续存储的队列元素反转。
// 来源：《2027数据结构》第3章 3.2.6 综合应用题02答案；PDF第100页；书页第88页。
bool InverseQueue(int *queue, size_t length) {
    int *stack;
    size_t stack_size = 0;
    if (length == 0) {
        return true;
    }
    if (queue == NULL || length > (size_t)-1 / sizeof(*stack)) {
        return false;
    }
    stack = (int *)malloc(length * sizeof(*stack));
    if (stack == NULL) {
        return false;
    }
    for (size_t i = 0; i < length; ++i) {
        stack[stack_size++] = queue[i];
    }
    for (size_t i = 0; i < length; ++i) {
        queue[i] = stack[--stack_size];
    }
    free(stack);
    return true;
}
