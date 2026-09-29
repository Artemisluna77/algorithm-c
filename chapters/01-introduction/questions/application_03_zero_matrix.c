#include "complexity_questions.h"

#include <stdint.h>
#include <stdlib.h>

// 功能：用两层循环将 rows×columns 的二维数组初始化为 0，按行主序返回连续存储区。
// 来源：《2027数据结构》第1章 1.2.3 综合应用题01③；PDF第20页；书页第8页。
int application_03_zero_matrix(size_t rows, size_t columns, int **matrix_out) {
    size_t count;
    if (matrix_out == NULL) return 0;
    *matrix_out = NULL;
    if (columns != 0 && rows > SIZE_MAX / columns) return 0;
    count = rows * columns;
    if (count == 0) return 1;
    if (count > SIZE_MAX / sizeof(int)) return 0;
    *matrix_out = (int *)calloc(count, sizeof(int));
    return *matrix_out != NULL;
}
