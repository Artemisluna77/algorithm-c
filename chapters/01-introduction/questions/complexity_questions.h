#ifndef CHAPTER01_COMPLEXITY_QUESTIONS_H
#define CHAPTER01_COMPLEXITY_QUESTIONS_H

#include <stddef.h>

// 功能：执行题干中的二倍递增循环，并返回结束时的 i 便于验证。
// 来源：《2027数据结构》第1章 1.2.3 试题06；PDF第18–19页；书页第6–7页。
long long q06_final_power_of_two(int n);

// 功能：按 i^3<=n 递增 i，返回首个使条件不成立的 i。
// 来源：《2027数据结构》第1章 1.2.3 试题07；PDF第19页；书页第7页。
int q07_first_cube_over_n(int n);

// 功能：统计逆序输入下冒泡程序中交换语句的执行次数。
// 来源：《2027数据结构》第1章 1.2.3 试题08；PDF第19页；书页第7页。
size_t q08_worst_case_bubble_swaps(size_t n);

// 功能：返回题干分支程序中 printf 被执行的次数。
// 来源：《2027数据结构》第1章 1.2.3 试题09；PDF第19页；书页第7页。
size_t q09_print_count(int n);

// 功能：累计 i 从 1 到 n、j 从 1 到 2i 时自增语句的执行次数。
// 来源：《2027数据结构》第1章 1.2.3 试题10；PDF第19页；书页第7页。
size_t q10_increment_count(size_t n);

// 功能：计算题干递归函数 Func(n)=2*Func(n/2)+n（n>=1）；成功返回非零，n<1 返回零。
// 来源：《2027数据结构》第1章 1.2.3 试题11；PDF第19页；书页第7页。
int q11_recursive_recurrence(int n, long long *result);

// 功能：执行从 x=2 开始的倍增循环，并返回结束时的 x。
// 来源：《2027数据结构》第1章 1.2.3 试题12；PDF第19页；书页第7页。
long long q12_final_doubled_value(int n);

// 功能：按题干递归定义计算非负整数 n 的阶乘；仅支持 0<=n<=20。
// 来源：《2027数据结构》第1章 1.2.3 试题13；PDF第19页；书页第7页。
int q13_factorial(int n, long long *result);

// 功能：统计外层 k 倍增、内层 j 从 1 到 n 的循环体执行次数。
// 来源：《2027数据结构》第1章 1.2.3 试题14；PDF第20页；书页第8页。
size_t q14_nested_loop_count(size_t n);

// 功能：逐项累加正整数，返回累计和首次达到 n 时的项数。
// 来源：《2027数据结构》第1章 1.2.3 试题15；PDF第20页；书页第8页。
int q15_triangular_sum_iterations(int n);

// 功能：递增 x 直到 (x+1)^2 超过 n，返回 floor(sqrt(n))。
// 来源：《2027数据结构》第1章 1.2.3 试题16；PDF第20页；书页第8页。
int q16_integer_square_root(int n);

// 功能：统计外层 i 倍增、内层 j<i 的循环体执行次数。
// 来源：《2027数据结构》第1章 1.2.3 试题17；PDF第20页；书页第8页。
size_t q17_geometric_nested_count(size_t n);

// 功能：统计 i*i<=n 时内层 j 从 1 到 i 的循环体执行次数。
// 来源：《2027数据结构》第1章 1.2.3 试题18；PDF第20页；书页第8页。
size_t q18_triangular_count(size_t n);

// 功能：执行 i 从 1 增长至 n-1 的线性累加程序段，返回 k。
// 来源：《2027数据结构》第1章 1.2.3 综合应用题01①；PDF第20页；书页第8页。
long long application_01_linear_accumulation(int n);

// 功能：执行题干中按平方条件递增 y 的循环，返回 floor(sqrt(n))。
// 来源：《2027数据结构》第1章 1.2.3 综合应用题01②；PDF第20页；书页第8页。
int application_02_integer_square_root(int n);

// 功能：用两层循环将 rows×columns 的二维数组初始化为 0；成功返回非零，调用方负责 free。
// 来源：《2027数据结构》第1章 1.2.3 综合应用题01③；PDF第20页；书页第8页。
int application_03_zero_matrix(size_t rows, size_t columns, int **matrix_out);

#endif
