#ifndef CH08_COMPARISON_COUNT_SORT_H
#define CH08_COMPARISON_COUNT_SORT_H

#include "../body/sorting_algorithms.h"

#include <stddef.h>

/* 功能：按两两比较得到的秩生成升序结果（题目 8.5.4 第03题，PDF 第381页，书页第369页）。 */
DsStatus ch08_comparison_count_sort(const int *values, size_t length,
                                    int *output);

#endif
