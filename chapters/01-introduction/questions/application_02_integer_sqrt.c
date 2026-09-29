#include "complexity_questions.h"

// 功能：执行题干中按平方条件递增 y 的循环，返回 floor(sqrt(n))。
// 来源：《2027数据结构》第1章 1.2.3 综合应用题01②；PDF第20页；书页第8页。
int application_02_integer_square_root(int n) {
    int y = 0;
    while ((long long)(y + 1) * (y + 1) <= n) ++y;
    return y;
}
