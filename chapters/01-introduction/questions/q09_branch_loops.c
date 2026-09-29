#include "complexity_questions.h"

// 功能：返回题干分支程序中 printf 被执行的次数。
// 来源：《2027数据结构》第1章 1.2.3 试题09；PDF第19页；书页第7页。
size_t q09_print_count(int n) {
    size_t count = 0;
    int i;
    int j;
    if (n >= 0) {
        for (i = 0; i < n; ++i) for (j = 0; j < n; ++j) ++count;
    } else {
        for (j = 0; j < n; ++j) ++count;
    }
    return count;
}
