#include "complexity_questions.h"

// 功能：累计 i 从 1 到 n、j 从 1 到 2i 时自增语句的执行次数。
// 来源：《2027数据结构》第1章 1.2.3 试题10；PDF第19页；书页第7页。
size_t q10_increment_count(size_t n) {
    size_t count = 0;
    size_t i;
    size_t j;
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= 2 * i; ++j) ++count;
    }
    return count;
}
