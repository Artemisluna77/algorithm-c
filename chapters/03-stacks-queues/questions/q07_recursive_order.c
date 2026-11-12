#include "recursion_snippets.h"

#include <stddef.h>

typedef struct {
    int values[16];
    size_t size;
} CallOrder;

static int func(int x, CallOrder *order) {
    if (order->size < sizeof(order->values) / sizeof(order->values[0])) {
        order->values[order->size++] = x;
    }
    if (x <= 3) {
        return 2;
    }
    return func(x - 2, order) + func(x - 4, order);
}

// 功能：记录 func(func(5)) 的调用顺序，并返回第 4 次调用使用的参数。
// 来源：《2027数据结构》第3章 3.3.6 试题07；PDF第107页；书页第95页。
int Q07FourthRecursiveCall(void) {
    CallOrder order = {{0}, 0};
    const int inner = func(5, &order);
    (void)func(inner, &order);
    return order.size >= 4 ? order.values[3] : -1;
}
