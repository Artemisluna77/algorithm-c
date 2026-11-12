#include "recursion_snippets.h"

#include <limits.h>
#include <stdint.h>

static int recursive_call_count(int n, int memo[89]) {
    int left;
    int right;
    int64_t count;
    if (n <= 3) {
        return 1;
    }
    if (memo[n] != 0) {
        return memo[n];
    }
    left = recursive_call_count(n - 2, memo);
    right = recursive_call_count(n - 4, memo);
    if (left < 0 || right < 0) {
        return -1;
    }
    count = 1 + (int64_t)left + right;
    if (count > INT_MAX) {
        return -1;
    }
    memo[n] = (int)count;
    return memo[n];
}

// 功能：递归计算调用树结点数，并记忆已算结果避免指数级重复计算；int 溢出时返回 -1。
// 来源：《2027数据结构》第3章 3.3.6 试题06；PDF第107页；书页第95页。
int Q06RecursiveCallCount(int n) {
    int memo[89] = {0};
    if (n > 88) {
        return -1;
    }
    return recursive_call_count(n, memo);
}
