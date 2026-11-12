#include "complexity_questions.h"

// 功能：按 i^3<=n 递增 i，返回首个使条件不成立的 i。
// 来源：《2027数据结构》第1章 1.2.3 试题07；PDF第19页；书页第7页。
int q07_first_cube_over_n(int n) {
    int i = 0;
    while ((long long)i * i * i <= n) ++i;
    return i;
}
