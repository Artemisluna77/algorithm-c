#include "stack_algorithms.h"
#include <stddef.h>

// 功能：逐个模拟 I 入栈与 O 出栈，拒绝空栈弹出并检查最终栈是否为空。
// 来源：《2027数据结构》第3章 3.1.4 综合应用题03答案；PDF第86页；书页第74页。
bool JudgeStackSequence(const char *operations) {
    size_t depth = 0;
    if (operations == NULL) {
        return false;
    }
    for (size_t i = 0; operations[i] != '\0'; ++i) {
        if (operations[i] == 'I') {
            ++depth;
        } else if (operations[i] == 'O') {
            if (depth == 0) {
                return false;
            }
            --depth;
        } else {
            return false;
        }
    }
    return depth == 0;
}
