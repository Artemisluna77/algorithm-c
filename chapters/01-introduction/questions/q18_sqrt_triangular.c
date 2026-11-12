#include "complexity_questions.h"

// 功能：统计 i*i<=n 时内层 j 从 1 到 i 的循环体执行次数。
// 来源：《2027数据结构》第1章 1.2.3 试题18；PDF第20页；书页第8页。
size_t q18_triangular_count(size_t n) {
    size_t count = 0;
    size_t i;
    size_t j;
    for (i = 1; i <= n / i; ++i) {
        for (j = 1; j <= i; ++j) ++count;
    }
    return count;
}
