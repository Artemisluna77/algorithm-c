#include "complexity_questions.h"

// 功能：执行 i 从 1 增长至 n-1 的线性累加程序段，返回 k。
// 来源：《2027数据结构》第1章 1.2.3 综合应用题01①；PDF第20页；书页第8页。
long long application_01_linear_accumulation(int n) {
    long long i = 1;
    long long k = 0;
    while (i < (long long)n - 1) {
        k += 10LL * i;
        ++i;
    }
    return k;
}
