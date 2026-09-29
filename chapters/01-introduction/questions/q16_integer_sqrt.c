#include "complexity_questions.h"

// 功能：递增 x 直到 (x+1)^2 超过 n，返回 floor(sqrt(n))。
// 来源：《2027数据结构》第1章 1.2.3 试题16；PDF第20页；书页第8页。
int q16_integer_square_root(int n) {
    int x = 0;
    while ((long long)n >= (long long)(x + 1) * (x + 1)) ++x;
    return x;
}
