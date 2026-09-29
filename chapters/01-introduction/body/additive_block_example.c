#include "complexity_examples.h"

// 功能：模拟顺序执行 O(1)、O(n)、O(n^2) 三个语句块的基本操作总数。
// 来源：《2027数据结构》第1章 1.2.2；PDF第18页；书页第6页。
size_t additive_block_work(size_t n) {
    size_t work = 1;
    size_t i;
    size_t j;
    for (i = 0; i < n; ++i) ++work;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) ++work;
    }
    return work;
}
