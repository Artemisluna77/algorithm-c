#ifndef CH03_SHARED_STACK_H
#define CH03_SHARED_STACK_H

#include <stdbool.h>

#define SHARED_STACK_MAX_SIZE 100

// 功能：定义两个栈共享一个数组的存储结构，两个栈顶从数组两端向中间增长。
// 来源：《2027数据结构》第3章 3.1.4 综合应用题05答案；PDF第87页；书页第75页。
typedef struct {
    int data[SHARED_STACK_MAX_SIZE];
    int top[2];
} SharedStack;

// 功能：初始化两个共享栈的栈顶指针，使其分别由数组两端向中间增长。
// 来源：《2027数据结构》第3章 3.1.4 综合应用题05答案；PDF第87页；书页第75页。
void InitSharedStack(SharedStack *stacks);

// 功能：向指定共享栈压入元素；栈号非法或两个栈顶相邻时失败。
// 来源：《2027数据结构》第3章 3.1.4 综合应用题05答案；PDF第87–88页；书页第75–76页。
bool SharedPush(SharedStack *stacks, int stack_number, int value);

// 功能：从指定共享栈弹出栈顶元素；栈号非法、栈为空或参数无效时返回 false。
// 来源：《2027数据结构》第3章 3.1.4 综合应用题05答案；PDF第87–88页；书页第75–76页。
bool SharedPop(SharedStack *stacks, int stack_number, int *value);

#endif
