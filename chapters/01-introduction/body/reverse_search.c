#include "complexity_examples.h"

// 功能：从数组尾部向前查找目标值，返回从 0 开始的位置，未找到返回 -1。
// 来源：《2027数据结构》第1章 1.2.2；PDF第17页；书页第5页。
int reverse_find(const int *values, size_t length, int target) {
    size_t i;
    if (values == NULL) return -1;
    for (i = length; i > 0; --i) {
        if (values[i - 1] == target) return (int)(i - 1);
    }
    return -1;
}
