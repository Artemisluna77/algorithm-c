#include "complexity_questions.h"

// 功能：按题干递归定义计算非负整数 n 的阶乘；仅支持 0<=n<=20。
// 来源：《2027数据结构》第1章 1.2.3 试题13；PDF第19页；书页第7页。
static long long factorial_value(int n) {
    if (n <= 1) return 1;
    return (long long)n * factorial_value(n - 1);
}

int q13_factorial(int n, long long *result) {
    if (n < 0 || n > 20 || result == NULL) return 0;
    *result = factorial_value(n);
    return 1;
}
