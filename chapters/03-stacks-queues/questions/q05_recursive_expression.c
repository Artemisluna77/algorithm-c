#include "recursion_snippets.h"

static int f(int x) {
    return x > 0 ? x * f(x - 1) : 2;
}

// 功能：执行题干中的递归函数嵌套调用 f(f(1))。
// 来源：《2027数据结构》第3章 3.3.6 试题05；PDF第106页；书页第94页。
int Q05RecursiveExpression(void) {
    return f(f(1));
}
