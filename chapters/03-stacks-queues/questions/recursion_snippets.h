#ifndef CH03_RECURSION_SNIPPETS_H
#define CH03_RECURSION_SNIPPETS_H

#include <stdbool.h>

// 功能：执行题干递归函数 f(f(1)) 并返回结果。
// 来源：《2027数据结构》第3章 3.3.6 试题05；PDF第106页；书页第94页。
int Q05RecursiveExpression(void);

// 功能：按调用数递归定义计算 F(n) 的总调用次数；无法用 int 表示时返回 -1。
// 来源：《2027数据结构》第3章 3.3.6 试题06；PDF第107页；书页第95页。
int Q06RecursiveCallCount(int n);

// 功能：记录 func(func(5)) 调用过程中第 4 次调用 func 的参数。
// 来源：《2027数据结构》第3章 3.3.6 试题07；PDF第107页；书页第95页。
int Q07FourthRecursiveCall(void);

// 功能：按题干递归定义计算 S(n)，S(n)=20 (n<=0)，否则 S(n-1)+n；结果越界时返回 -1。
// 来源：《2027数据结构》第3章 3.3.6 试题15；PDF第107页；书页第95页。
int Q15RecursiveSum(int n);

#endif
