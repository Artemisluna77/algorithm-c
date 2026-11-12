#include "complexity_examples.h"

// 功能：按平方条件逐次增加 y，返回满足循环条件的最大 y。
// 来源：《2027数据结构》第1章 归纳总结；PDF第23页；书页第11页。
int summary_square_root_loop(int n) {
    int y = 5;
    while ((long long)(y + 1) * (y + 1) < n) ++y;
    return y;
}
