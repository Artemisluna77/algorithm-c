#include "stack_algorithms.h"

#include <stdlib.h>

// 功能：压入字符序列前半段，再逐个比较后半段。
// 来源：《2027数据结构》第3章 3.1.4 综合应用题04答案；PDF第86页；书页第74页。
bool IsLinkedListPalindrome(const char *values, size_t length) {
    const size_t half = length / 2;
    char *first_half;
    if (length == 0) {
        return true;
    }
    if (values == NULL) {
        return false;
    }
    if (half == 0) {
        return true;
    }
    first_half = (char *)malloc(half);
    if (first_half == NULL) {
        return false;
    }
    for (size_t i = 0; i < half; ++i) {
        first_half[i] = values[i];
    }
    for (size_t i = 0; i < half; ++i) {
        const size_t right_index = half + (length % 2) + i;
        if (first_half[half - 1 - i] != values[right_index]) {
            free(first_half);
            return false;
        }
    }
    free(first_half);
    return true;
}
