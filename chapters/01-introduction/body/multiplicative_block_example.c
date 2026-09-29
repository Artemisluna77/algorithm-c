#include "complexity_examples.h"

// 功能：模拟 O(1) 语句块中嵌套 O(n) 与 O(n^2) 语句块的基本操作总数。
// 来源：《2027数据结构》第1章 1.2.2；PDF第18页；书页第6页。
size_t multiplicative_block_work(size_t n) {
    size_t work = 1;
    size_t i;
    size_t j;
    size_t k;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            for (k = 0; k < n; ++k) ++work;
        }
    }
    return work;
}
