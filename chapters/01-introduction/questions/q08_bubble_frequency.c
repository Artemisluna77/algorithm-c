#include "complexity_questions.h"

// 功能：统计逆序输入下冒泡程序中交换语句的执行次数。
// 来源：《2027数据结构》第1章 1.2.3 试题08；PDF第19页；书页第7页。
size_t q08_worst_case_bubble_swaps(size_t n) {
    size_t i;
    size_t count = 0;
    if (n < 3) return 0;
    for (i = n - 1; i > 1; --i) count += i - 1;
    return count;
}
