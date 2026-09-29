#include "sorting_algorithms.h"
#include "sorting_answers.h"
#include "comparison_count_sort.h"
#include "sorting_exploration.h"
#include "test_harness.h"

#include <limits.h>
#include <stddef.h>

/* 功能：比较数组内容与预期序列，供排序测试复用。 */
static void expect_values(const int *actual, const int *expected, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        DS_CHECK(actual[i] == expected[i]);
    }
}

/* 功能：验证交换操作支持普通元素、自交换和空指针。 */
DS_TEST_FUNCTION(swap_values) {
    int left = -3;
    int right = 8;
    ch08_swap_values(&left, &right);
    DS_CHECK(left == 8);
    DS_CHECK(right == -3);
    ch08_swap_values(&left, &left);
    DS_CHECK(left == 8);
    ch08_swap_values(NULL, &right);
    DS_CHECK(right == -3);
}

/* 功能：验证直接插入排序处理乱序、重复值、空数组和非法空指针。 */
DS_TEST_FUNCTION(insertion_sort) {
    int values[] = {49, 38, 65, 97, 76, 13, 27, 49};
    const int expected[] = {13, 27, 38, 49, 49, 65, 76, 97};
    DS_CHECK(ch08_insertion_sort(values, 8) == DS_STATUS_OK);
    expect_values(values, expected, 8);
    DS_CHECK(ch08_insertion_sort(NULL, 0) == DS_STATUS_OK);
    DS_CHECK(ch08_insertion_sort(NULL, 1) == DS_STATUS_INVALID_ARGUMENT);
}

/* 功能：验证折半插入排序的重复值与空数组边界。 */
DS_TEST_FUNCTION(binary_insertion_sort) {
    int values[] = {5, 2, 2, -1, 9, 0};
    const int expected[] = {-1, 0, 2, 2, 5, 9};
    DS_CHECK(ch08_binary_insertion_sort(values, 6) == DS_STATUS_OK);
    expect_values(values, expected, 6);
    DS_CHECK(ch08_binary_insertion_sort(NULL, 0) == DS_STATUS_OK);
}

/* 功能：验证希尔排序覆盖负值、重复值及已有序序列。 */
DS_TEST_FUNCTION(shell_sort) {
    int values[] = {49, 38, 65, 97, 76, 13, 27, 49};
    const int expected[] = {13, 27, 38, 49, 49, 65, 76, 97};
    DS_CHECK(ch08_shell_sort(values, 8) == DS_STATUS_OK);
    expect_values(values, expected, 8);
    int sorted[] = {-3, -2, -2, 0, 1};
    const int sorted_expected[] = {-3, -2, -2, 0, 1};
    DS_CHECK(ch08_shell_sort(sorted, 5) == DS_STATUS_OK);
    expect_values(sorted, sorted_expected, 5);
}

/* 功能：验证冒泡排序的提前结束、一般输入和单元素边界。 */
DS_TEST_FUNCTION(bubble_sort) {
    int values[] = {5, 1, 4, 2, 8, 1};
    const int expected[] = {1, 1, 2, 4, 5, 8};
    DS_CHECK(ch08_bubble_sort(values, 6) == DS_STATUS_OK);
    expect_values(values, expected, 6);
    int one[] = {7};
    DS_CHECK(ch08_bubble_sort(one, 1) == DS_STATUS_OK);
    DS_CHECK(one[0] == 7);
}

/* 功能：验证快速排序处理重复值、已排序数组、退化大数组和空输入。 */
DS_TEST_FUNCTION(quick_sort) {
    int values[] = {9, -4, 7, 7, 1, 0, -4, 8};
    const int expected[] = {-4, -4, 0, 1, 7, 7, 8, 9};
    DS_CHECK(ch08_quick_sort(values, 8) == DS_STATUS_OK);
    expect_values(values, expected, 8);
    int duplicates[3000];
    for (size_t i = 0; i < 3000; ++i) duplicates[i] = 5;
    DS_CHECK(ch08_quick_sort(duplicates, 3000) == DS_STATUS_OK);
    for (size_t i = 0; i < 3000; ++i) DS_CHECK(duplicates[i] == 5);
    DS_CHECK(ch08_quick_sort(NULL, 0) == DS_STATUS_OK);
}

/* 功能：验证首元素枢轴划分的左右分区性质及非法闭区间处理。 */
DS_TEST_FUNCTION(first_pivot_partition) {
    int values[] = {4, 7, 2, 4, 1, 6};
    size_t pivot = 0;
    DS_CHECK(ch08_partition_first_pivot(values, 6, 0, 5, &pivot) == DS_STATUS_OK);
    DS_CHECK(values[pivot] == 4);
    for (size_t i = 0; i < pivot; ++i) DS_CHECK(values[i] <= 4);
    for (size_t i = pivot + 1; i < 6; ++i) DS_CHECK(values[i] >= 4);
    DS_CHECK(ch08_partition_first_pivot(values, 6, 0, 6, &pivot) == DS_STATUS_INVALID_ARGUMENT);
    DS_CHECK(ch08_partition_first_pivot(values, 6, 3, 2, &pivot) == DS_STATUS_INVALID_ARGUMENT);
}

/* 功能：验证简单选择排序对重复键和空数组的处理。 */
DS_TEST_FUNCTION(selection_sort) {
    int values[] = {4, 2, 4, -1, 0};
    const int expected[] = {-1, 0, 2, 4, 4};
    DS_CHECK(ch08_selection_sort(values, 5) == DS_STATUS_OK);
    expect_values(values, expected, 5);
    DS_CHECK(ch08_selection_sort(NULL, 0) == DS_STATUS_OK);
}

/* 功能：验证最大堆子树向下调整并拒绝空指针非空长度。 */
DS_TEST_FUNCTION(heap_adjust) {
    int values[] = {1, 9, 8, 7, 6, 5, 4};
    DS_CHECK(ch08_heap_adjust(values, 7, 0) == DS_STATUS_OK);
    DS_CHECK(values[0] == 9);
    for (size_t child = 1; child < 7; ++child) {
        DS_CHECK(values[(child - 1) / 2] >= values[child]);
    }
    DS_CHECK(ch08_heap_adjust(NULL, 2, 0) == DS_STATUS_INVALID_ARGUMENT);
}

/* 功能：验证建堆输出满足最大堆性质，且空堆可安全处理。 */
DS_TEST_FUNCTION(build_max_heap) {
    int values[] = {3, 1, 6, 5, 2, 4};
    DS_CHECK(ch08_build_max_heap(values, 6) == DS_STATUS_OK);
    for (size_t child = 1; child < 6; ++child) {
        DS_CHECK(values[(child - 1) / 2] >= values[child]);
    }
    DS_CHECK(values[0] == 6);
    DS_CHECK(ch08_build_max_heap(NULL, 0) == DS_STATUS_OK);
}

/* 功能：验证堆排序的升序结果和单元素边界。 */
DS_TEST_FUNCTION(heap_sort) {
    int values[] = {3, 2, 1, 6, 5, 4, -1, 6};
    const int expected[] = {-1, 1, 2, 3, 4, 5, 6, 6};
    DS_CHECK(ch08_heap_sort(values, 8) == DS_STATUS_OK);
    expect_values(values, expected, 8);
    int one[] = {1};
    DS_CHECK(ch08_heap_sort(one, 1) == DS_STATUS_OK);
    DS_CHECK(one[0] == 1);
}

/* 功能：验证相邻有序区间合并及非法边界。 */
DS_TEST_FUNCTION(merge_ranges) {
    int values[] = {1, 4, 7, 2, 3, 8, 99};
    const int expected[] = {1, 2, 3, 4, 7, 8, 99};
    DS_CHECK(ch08_merge_sorted_ranges(values, 7, 0, 3, 6) == DS_STATUS_OK);
    expect_values(values, expected, 7);
    DS_CHECK(ch08_merge_sorted_ranges(values, 7, 0, 8, 7) == DS_STATUS_INVALID_ARGUMENT);
    DS_CHECK(ch08_merge_sorted_ranges(NULL, 0, 0, 0, 0) == DS_STATUS_OK);
}

/* 功能：验证稳定归并排序覆盖重复值、负数和空数组。 */
DS_TEST_FUNCTION(merge_sort) {
    int values[] = {38, 49, 65, 97, 76, 13, 27, 49};
    const int expected[] = {13, 27, 38, 49, 49, 65, 76, 97};
    DS_CHECK(ch08_merge_sort(values, 8) == DS_STATUS_OK);
    expect_values(values, expected, 8);
    DS_CHECK(ch08_merge_sort(NULL, 0) == DS_STATUS_OK);
}

/* 功能：验证计数排序的输出、空输入及取值范围校验。 */
DS_TEST_FUNCTION(counting_sort) {
    const int values[] = {2, 4, 3, 0, 2, 3};
    int output[6] = {0};
    const int expected[] = {0, 2, 2, 3, 3, 4};
    DS_CHECK(ch08_counting_sort(values, 6, 5, output) == DS_STATUS_OK);
    expect_values(output, expected, 6);
    const int invalid[] = {-1, 0};
    DS_CHECK(ch08_counting_sort(invalid, 2, 5, output) == DS_STATUS_INVALID_VALUE);
    DS_CHECK(ch08_counting_sort(NULL, 0, 0, NULL) == DS_STATUS_OK);
}

/* 功能：验证负数奇偶判定以及偶数在左、奇数在右的划分性质。 */
DS_TEST_FUNCTION(move_even_before_odd) {
    int values[] = {1, 2, -3, 4, 0, -8, 7};
    DS_CHECK(ch08_move_even_before_odd(values, 7) == DS_STATUS_OK);
    int saw_odd = 0;
    for (size_t i = 0; i < 7; ++i) {
        if (values[i] % 2 != 0) saw_odd = 1;
        if (saw_odd) DS_CHECK(values[i] % 2 != 0);
        else DS_CHECK(values[i] % 2 == 0);
    }
    DS_CHECK(ch08_move_even_before_odd(NULL, 0) == DS_STATUS_OK);
}

/* 功能：验证第 k 小元素、输入保持不变以及非法 k。 */
DS_TEST_FUNCTION(kth_element) {
    const int values[] = {7, 2, 9, 2, -1, 4};
    int result = 0;
    DS_CHECK(ch08_kth_element(values, 6, 1, &result) == DS_STATUS_OK && result == -1);
    DS_CHECK(ch08_kth_element(values, 6, 3, &result) == DS_STATUS_OK && result == 2);
    DS_CHECK(ch08_kth_element(values, 6, 6, &result) == DS_STATUS_OK && result == 9);
    DS_CHECK(values[0] == 7);
    DS_CHECK(ch08_kth_element(values, 6, 0, &result) == DS_STATUS_INVALID_ARGUMENT);
}

/* 功能：验证荷兰国旗三路整理、空输入和非法颜色值。 */
DS_TEST_FUNCTION(arrange_flag) {
    Color colors[] = {COLOR_WHITE, COLOR_BLUE, COLOR_RED, COLOR_BLUE,
                      COLOR_WHITE, COLOR_RED, COLOR_RED};
    DS_CHECK(ch08_arrange_flag(colors, 7) == DS_STATUS_OK);
    int phase = 0;
    for (size_t i = 0; i < 7; ++i) {
        if (colors[i] == COLOR_RED) DS_CHECK(phase == 0);
        else if (colors[i] == COLOR_WHITE) { DS_CHECK(phase <= 1); phase = 1; }
        else { DS_CHECK(colors[i] == COLOR_BLUE); phase = 2; }
    }
    Color invalid[] = {COLOR_WHITE, COLOR_RED, (Color)3};
    DS_CHECK(ch08_arrange_flag(invalid, 3) == DS_STATUS_INVALID_VALUE);
    DS_CHECK(invalid[0] == COLOR_WHITE && invalid[1] == COLOR_RED &&
             (int)invalid[2] == 3);
    DS_CHECK(ch08_arrange_flag(NULL, 0) == DS_STATUS_OK);
}

/* 功能：验证中位数划分的分区与和差，并覆盖短输入和 int 溢出边界。 */
DS_TEST_FUNCTION(balanced_partition) {
    int values[] = {9, 1, 7, 2, 8, 3, 6};
    int difference = 0;
    DS_CHECK(ch08_partition_for_balance(values, 7, &difference) == DS_STATUS_OK);
    for (size_t left = 0; left < 3; ++left) {
        for (size_t right = 3; right < 7; ++right) {
            DS_CHECK(values[left] <= values[right]);
        }
    }
    int small[] = {1};
    DS_CHECK(ch08_partition_for_balance(small, 1, &difference) == DS_STATUS_INVALID_ARGUMENT);
    int extremes[] = {INT_MIN, INT_MAX};
    DS_CHECK(ch08_partition_for_balance(extremes, 2, &difference) == DS_STATUS_OVERFLOW);
}

/* 功能：验证单链表选择排序重连原结点且不泄漏节点。 */
DS_TEST_FUNCTION(linked_list_selection_sort) {
    DsIntNode n5 = {4, NULL};
    DsIntNode n4 = {1, &n5};
    DsIntNode n3 = {3, &n4};
    DsIntNode n2 = {1, &n3};
    DsIntNode n1 = {-2, &n2};
    DsIntNode *node = ch08_linked_list_selection_sort(&n1);
    const int expected[] = {-2, 1, 1, 3, 4};
    for (size_t i = 0; i < 5; ++i) {
        DS_CHECK(node != NULL && node->value == expected[i]);
        if (node != NULL) node = node->next;
    }
    DS_CHECK(node == NULL);
    DS_CHECK(ch08_linked_list_selection_sort(NULL) == NULL);
}

/* 功能：验证小根堆判断接受空/单元素堆并拒绝违反父子序的数组。 */
DS_TEST_FUNCTION(is_min_heap) {
    const int valid[] = {1, 3, 2, 7, 6, 5, 4};
    const int invalid[] = {1, 3, 2, 0};
    DS_CHECK(ch08_is_min_heap(valid, 7));
    DS_CHECK(!ch08_is_min_heap(invalid, 4));
    DS_CHECK(ch08_is_min_heap(NULL, 0));
    DS_CHECK(!ch08_is_min_heap(NULL, 1));
}

/* 功能：验证优先队列最大堆入队/出队、满队列、空队列和资源释放。 */
DS_TEST_FUNCTION(priority_queue_operations) {
    DsPriorityQueue queue;
    PriorityQueueElement result;
    DS_CHECK(ch08_priority_queue_init(&queue, 3) == DS_STATUS_OK);
    DS_CHECK(ch08_priority_queue_enqueue(&queue, (PriorityQueueElement){10, 1}) == DS_STATUS_OK);
    DS_CHECK(ch08_priority_queue_enqueue(&queue, (PriorityQueueElement){20, 8}) == DS_STATUS_OK);
    DS_CHECK(ch08_priority_queue_enqueue(&queue, (PriorityQueueElement){30, 4}) == DS_STATUS_OK);
    DS_CHECK(ch08_priority_queue_enqueue(&queue, (PriorityQueueElement){40, 2}) == DS_STATUS_FULL);
    DS_CHECK(ch08_priority_queue_dequeue(&queue, &result) == DS_STATUS_OK);
    DS_CHECK(result.value == 20 && result.priority == 8);
    DS_CHECK(ch08_priority_queue_enqueue(&queue, (PriorityQueueElement){40, 12}) == DS_STATUS_OK);
    DS_CHECK(ch08_priority_queue_dequeue(&queue, &result) == DS_STATUS_OK && result.value == 40);
    DS_CHECK(ch08_priority_queue_dequeue(&queue, &result) == DS_STATUS_OK && result.value == 30);
    DS_CHECK(ch08_priority_queue_dequeue(&queue, &result) == DS_STATUS_OK && result.value == 10);
    DS_CHECK(ch08_priority_queue_dequeue(&queue, &result) == DS_STATUS_EMPTY);
    ch08_priority_queue_destroy(&queue);
    DS_CHECK(queue.heap == NULL && queue.size == 0 && queue.capacity == 0);
    DS_CHECK(ch08_priority_queue_init(&queue, 0) == DS_STATUS_OK);
    DS_CHECK(ch08_priority_queue_enqueue(&queue, (PriorityQueueElement){1, 1}) == DS_STATUS_FULL);
    ch08_priority_queue_destroy(&queue);
}

/* 功能：验证从已排序前缀接续插入排序及无效前缀处理。 */
DS_TEST_FUNCTION(insertion_sort_suffix) {
    int values[] = {1, 3, 5, 4, 2, 6};
    const int expected[] = {1, 2, 3, 4, 5, 6};
    DS_CHECK(ch08_insertion_sort_suffix(values, 6, 3) == DS_STATUS_OK);
    expect_values(values, expected, 6);
    DS_CHECK(ch08_insertion_sort_suffix(values, 6, 7) == DS_STATUS_INVALID_ARGUMENT);
    int unsorted[] = {3, 1, 2};
    DS_CHECK(ch08_insertion_sort_suffix(unsorted, 3, 2) == DS_STATUS_INVALID_VALUE);
}

/* 功能：验证末元素枢轴划分结果和空数组错误。 */
DS_TEST_FUNCTION(last_pivot_partition) {
    int values[] = {4, 7, 2, 5, 1};
    size_t pivot = 0;
    DS_CHECK(ch08_partition_last_pivot(values, 5, &pivot) == DS_STATUS_OK);
    DS_CHECK(values[pivot] == 1);
    for (size_t i = 0; i < pivot; ++i) DS_CHECK(values[i] <= 1);
    for (size_t i = pivot + 1; i < 5; ++i) DS_CHECK(values[i] >= 1);
    DS_CHECK(ch08_partition_last_pivot(NULL, 0, &pivot) == DS_STATUS_INVALID_ARGUMENT);
}

/* 功能：验证两两比较计数排序处理重复键、空数组和原地输出。 */
DS_TEST_FUNCTION(comparison_count_sort) {
    int values[] = {25, -10, 25, 10, 11, 19};
    const int expected[] = {-10, 10, 11, 19, 25, 25};
    DS_CHECK(ch08_comparison_count_sort(values, 6, values) == DS_STATUS_OK);
    expect_values(values, expected, 6);
    DS_CHECK(ch08_comparison_count_sort(NULL, 0, NULL) == DS_STATUS_OK);
}

/* 功能：验证稳定性修正分支对相等和不等关键字的计数。 */
DS_TEST_FUNCTION(stable_pair_count_fragment) {
    size_t earlier_count = 0;
    size_t later_count = 0;
    DS_CHECK(ch08_count_stable_pair(7, 7, &earlier_count, &later_count) == DS_STATUS_OK);
    DS_CHECK(earlier_count == 0 && later_count == 1);
    DS_CHECK(ch08_count_stable_pair(9, 3, &earlier_count, &later_count) == DS_STATUS_OK);
    DS_CHECK(earlier_count == 1 && later_count == 1);
}

/* 功能：验证思维拓展频数排序对固定小值域及负数偏移的处理。 */
DS_TEST_FUNCTION(range_frequency_sort) {
    int values[] = {7, -2, 3, 3, 0, -2};
    const int expected[] = {-2, -2, 0, 3, 3, 7};
    DS_CHECK(ch08_frequency_sort_signed(values, 6) == DS_STATUS_OK);
    expect_values(values, expected, 6);
    int signed_16bit[] = {32767, -32768, 0};
    const int signed_16bit_expected[] = {-32768, 0, 32767};
    DS_CHECK(ch08_frequency_sort_signed(signed_16bit, 3) == DS_STATUS_OK);
    expect_values(signed_16bit, signed_16bit_expected, 3);
    DS_CHECK(ch08_frequency_sort_signed(NULL, 0) == DS_STATUS_OK);
    DS_CHECK(ch08_frequency_sort_signed(NULL, 1) == DS_STATUS_INVALID_ARGUMENT);
    int too_wide[] = {INT_MIN, INT_MAX};
    DS_CHECK(ch08_frequency_sort_signed(too_wide, 2) == DS_STATUS_INVALID_VALUE);
}

int main(int argc, char **argv) {
    static const DsTestCase cases[] = {
        DS_TEST_CASE(swap_values),
        DS_TEST_CASE(insertion_sort),
        DS_TEST_CASE(binary_insertion_sort),
        DS_TEST_CASE(shell_sort),
        DS_TEST_CASE(bubble_sort),
        DS_TEST_CASE(quick_sort),
        DS_TEST_CASE(first_pivot_partition),
        DS_TEST_CASE(selection_sort),
        DS_TEST_CASE(heap_adjust),
        DS_TEST_CASE(build_max_heap),
        DS_TEST_CASE(heap_sort),
        DS_TEST_CASE(merge_ranges),
        DS_TEST_CASE(merge_sort),
        DS_TEST_CASE(counting_sort),
        DS_TEST_CASE(move_even_before_odd),
        DS_TEST_CASE(kth_element),
        DS_TEST_CASE(arrange_flag),
        DS_TEST_CASE(balanced_partition),
        DS_TEST_CASE(linked_list_selection_sort),
        DS_TEST_CASE(is_min_heap),
        DS_TEST_CASE(priority_queue_operations),
        DS_TEST_CASE(insertion_sort_suffix),
        DS_TEST_CASE(last_pivot_partition),
        DS_TEST_CASE(comparison_count_sort),
        DS_TEST_CASE(stable_pair_count_fragment),
        DS_TEST_CASE(range_frequency_sort)
    };
    return ds_test_run(argc, argv, cases, sizeof(cases) / sizeof(cases[0]));
}
