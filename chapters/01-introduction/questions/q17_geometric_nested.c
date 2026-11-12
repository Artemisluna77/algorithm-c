#include "complexity_questions.h"

// 功能：统计外层 i 倍增、内层 j<i 的循环体执行次数。
// 来源：《2027数据结构》第1章 1.2.3 试题17；PDF第20页；书页第8页。
size_t q17_geometric_nested_count(size_t n) {
    size_t count = 0;
    size_t i;
    size_t j;
    for (i = 1; i < n; i *= 2) {
        for (j = 0; j < i; ++j) ++count;
        if (i > n / 2) break;
    }
    return count;
}
