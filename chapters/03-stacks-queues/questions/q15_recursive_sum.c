#include "recursion_snippets.h"

#include <limits.h>
#include <stdint.h>

// 功能：按题干递归函数计算 S(n)，非正数时返回 20；使用等价累加避免深递归，int 越界时返回 -1。
// 来源：《2027数据结构》第3章 3.3.6 试题15；PDF第107页；书页第95页。
int Q15RecursiveSum(int n) {
    int64_t sum = 20;
    if (n <= 0) {
        return 20;
    }
    for (int current = 1; current <= n; ++current) {
        sum += current;
        if (sum > INT_MAX) {
            return -1;
        }
    }
    return (int)sum;
}
