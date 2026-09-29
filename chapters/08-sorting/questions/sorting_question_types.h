#ifndef CH08_SORTING_QUESTION_TYPES_H
#define CH08_SORTING_QUESTION_TYPES_H

/* 功能：表示荷兰国旗问题给出的三种颜色（第8章 8.3.4 第03题，PDF 第358页，书页第346页）。 */
typedef enum Color {
    COLOR_RED = 0,
    COLOR_WHITE = 1,
    COLOR_BLUE = 2
} Color;

/* 功能：保存优先队列元素及其优先级（第8章 8.4.3 第07题，PDF 第368页，书页第356页）。 */
typedef struct PriorityQueueElement {
    int value;
    int priority;
} PriorityQueueElement;

/* 功能：声明题目要求的荷兰国旗排序函数；完整实现另归答案类别（PDF 第358页，书页第346页）。 */
void Flag_Arrange(Color colors[], int length);

#endif
