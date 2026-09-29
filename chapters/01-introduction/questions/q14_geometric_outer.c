#include "complexity_questions.h"

// 功能：统计外层 k 倍增、内层 j 从 1 到 n 的循环体执行次数。
// 来源：《2027数据结构》第1章 1.2.3 试题14；PDF第20页；书页第8页。
size_t q14_nested_loop_count(size_t n) {
    size_t count = 0;
    size_t k;
    size_t j;
    for (k = 1; k <= n; k *= 2) {
        for (j = 1; j <= n; ++j) ++count;
        if (k > n / 2) break;
    }
    return count;
}
