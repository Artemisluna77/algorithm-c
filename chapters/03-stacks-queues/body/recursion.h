#ifndef CH03_RECURSION_H
#define CH03_RECURSION_H

#include <stdbool.h>

// 功能：按递归定义计算 Fibonacci 数 F(n)，边界为 F(0)=0、F(1)=1；仅接受 [0,46] 以保证 int 不溢出。
// 来源：《2027数据结构》第3章 3.3.3；PDF第104页；书页第92页。
bool Fibonacci(int n, int *result);

#endif
