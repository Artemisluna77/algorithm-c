#include "complexity_questions.h"

// 功能：执行从 x=2 开始的倍增循环，并返回结束时的 x。
// 来源：《2027数据结构》第1章 1.2.3 试题12；PDF第19页；书页第7页。
long long q12_final_doubled_value(int n) {
    long long x = 2;
    while (x < n / 2) x *= 2;
    return x;
}
