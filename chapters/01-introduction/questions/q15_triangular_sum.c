#include "complexity_questions.h"

// 功能：逐项累加正整数，返回累计和首次达到 n 时的项数。
// 来源：《2027数据结构》第1章 1.2.3 试题15；PDF第20页；书页第8页。
int q15_triangular_sum_iterations(int n) {
    int i = 0;
    long long sum = 0;
    while (sum < n) sum += ++i;
    return i;
}
