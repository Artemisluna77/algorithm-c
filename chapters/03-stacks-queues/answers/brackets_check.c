#include "brackets_check.h"

#include <stdlib.h>
#include <string.h>

// 功能：遇左括号入栈，遇右括号时与栈顶匹配，最终要求栈为空。
// 来源：《2027数据结构》第3章 3.3.7 综合应用题01答案；PDF第112页；书页第100页。
bool BracketsCheck(const char *expression) {
    size_t length;
    size_t top = 0;
    char *expected;
    bool valid = true;
    if (expression == NULL) {
        return false;
    }
    length = strlen(expression);
    if (length == 0) {
        return true;
    }
    expected = (char *)malloc(length);
    if (expected == NULL) {
        return false;
    }
    for (size_t i = 0; i < length; ++i) {
        const char symbol = expression[i];
        if (symbol == '(') {
            expected[top++] = ')';
        } else if (symbol == '[') {
            expected[top++] = ']';
        } else if (symbol == '{') {
            expected[top++] = '}';
        } else if (symbol == ')' || symbol == ']' || symbol == '}') {
            if (top == 0 || expected[top - 1] != symbol) {
                valid = false;
                break;
            }
            --top;
        }
    }
    valid = valid && top == 0;
    free(expected);
    return valid;
}
