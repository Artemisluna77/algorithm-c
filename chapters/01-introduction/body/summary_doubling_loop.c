#include "complexity_examples.h"

// 功能：按 i 从 1 开始不断乘 2 的示例循环，返回结束时 i。
// 来源：《2027数据结构》第1章 归纳总结；PDF第23页；书页第11页。
long long summary_doubling_loop(int n) {
    long long i = 1;
    while (i <= n) i *= 2;
    return i;
}
