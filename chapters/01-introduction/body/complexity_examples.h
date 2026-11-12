#ifndef CHAPTER01_COMPLEXITY_EXAMPLES_H
#define CHAPTER01_COMPLEXITY_EXAMPLES_H

#include <stddef.h>

// 功能：从数组尾部向前查找目标值，返回从 0 开始的位置，未找到返回 -1。
// 来源：《2027数据结构》第1章 1.2.2；PDF第17页；书页第5页。
int reverse_find(const int *values, size_t length, int target);

// 功能：模拟顺序执行 O(1)、O(n)、O(n^2) 三个语句块的基本操作总数。
// 来源：《2027数据结构》第1章 1.2.2；PDF第18页；书页第6页。
size_t additive_block_work(size_t n);

// 功能：模拟 O(1) 语句块中嵌套 O(n) 与 O(n^2) 语句块的基本操作总数。
// 来源：《2027数据结构》第1章 1.2.2；PDF第18页；书页第6页。
size_t multiplicative_block_work(size_t n);

// 功能：按 i 从 1 开始不断乘 2 的示例循环，返回结束时 i。
// 来源：《2027数据结构》第1章 归纳总结；PDF第23页；书页第11页。
long long summary_doubling_loop(int n);

// 功能：按平方条件逐次增加 y，返回满足循环条件的最大 y。
// 来源：《2027数据结构》第1章 归纳总结；PDF第23页；书页第11页。
int summary_square_root_loop(int n);

#endif
