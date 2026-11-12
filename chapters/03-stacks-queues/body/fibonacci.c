#include "recursion.h"
#include <stddef.h>

static int fibonacci_memoized(int n, int memo[47]) {
    if (memo[n] >= 0) {
        return memo[n];
    }
    memo[n] = fibonacci_memoized(n - 1, memo) +
              fibonacci_memoized(n - 2, memo);
    return memo[n];
}

// 功能：依据书中递归关系计算 Fibonacci 数列；以记忆化避免指数重复计算；n 越界或结果参数为空时返回 false。
// 来源：《2027数据结构》第3章 3.3.3；PDF第104页；书页第92页。
bool Fibonacci(int n, int *result) {
    int memo[47];
    int i;
    if (result == NULL || n < 0 || n > 46) {
        return false;
    }
    for (i = 0; i < 47; ++i) {
        memo[i] = -1;
    }
    memo[0] = 0;
    memo[1] = 1;
    *result = fibonacci_memoized(n, memo);
    return true;
}
