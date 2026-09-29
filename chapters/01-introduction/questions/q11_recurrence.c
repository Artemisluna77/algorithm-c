#include "complexity_questions.h"

// 功能：计算题干递归函数 Func(n)=2*Func(n/2)+n（n>=1）。
// 来源：《2027数据结构》第1章 1.2.3 试题11；PDF第19页；书页第7页。
static long long recurrence_value(int n) {
    if (n == 1) return 1;
    return 2 * recurrence_value(n / 2) + n;
}

int q11_recursive_recurrence(int n, long long *result) {
    if (n < 1 || result == NULL) return 0;
    *result = recurrence_value(n);
    return 1;
}
