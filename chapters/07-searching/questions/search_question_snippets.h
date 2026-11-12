#ifndef CH07_SEARCH_QUESTION_SNIPPETS_H
#define CH07_SEARCH_QUESTION_SNIPPETS_H

#include "../body/search_algorithms.h"

#include <stddef.h>

/* 功能：按固定步长跳跃定位有序数组区间，再回看块内元素（第7章 7.2.2 试题22，PDF 第283页，书页第271页）。 */
Ch07Status ch07_stride_search(const int *sorted, size_t length, int key,
                              size_t step, size_t *index);

#endif
