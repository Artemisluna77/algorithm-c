#include "complexity_questions.h"

// 功能：执行题干中的二倍递增循环，并返回循环结束时的 i 便于验证。
// 来源：《2027数据结构》第1章 1.2.3 试题06；PDF第18–19页；书页第6–7页。
long long q06_final_power_of_two(int n) {
    long long i = 1;
    while (i <= n) i *= 2;
    return i;
}
