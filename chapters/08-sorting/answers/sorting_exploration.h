#ifndef CH08_SORTING_EXPLORATION_H
#define CH08_SORTING_EXPLORATION_H

#include "../body/sorting_algorithms.h"

#include <stddef.h>

/* 功能：按最小值偏移后的固定 65536 桶频数表排序有符号整数（第8章“思维拓展”提示，PDF 第403页，书页第391页）。 */
DsStatus ch08_frequency_sort_signed(int *values, size_t length);

#endif
