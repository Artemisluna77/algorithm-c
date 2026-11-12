#include "sequential_algorithms.h"
#include "test_harness.h"

#include <stddef.h>

static SeqList make_list(const int *values, size_t length) {
    SeqList result = {0};
    size_t i;
    SeqListInit(&result);
    for (i = 0; i < length; ++i) SeqListInsert(&result, result.length + 1, values[i]);
    return result;
}

static int expect_list(const SeqList *list, const int *expected, size_t length) {
    size_t i;
    if (list == NULL || list->length != length) return 0;
    for (i = 0; i < length; ++i) if (list->data[i] != expected[i]) return 0;
    return 1;
}

DS_TEST_FUNCTION(delete_minimum) {
    const int input[] = {7, 2, 9, 2};
    const int expected[] = {7, 2, 9};
    SeqList list = make_list(input, 4);
    SeqList empty = {0};
    int minimum = -1;
    DS_CHECK(delete_minimum(&list, &minimum) && minimum == 2);
    DS_CHECK(expect_list(&list, expected, 3));
    SeqListInit(&empty);
    DS_CHECK(!delete_minimum(&empty, &minimum));
}

DS_TEST_FUNCTION(reverse_sequence) {
    const int input[] = {1, 2, 3, 4, 5};
    const int expected[] = {5, 4, 3, 2, 1};
    SeqList list = make_list(input, 5);
    SeqList empty = {0};
    reverse_sequential_list(&list);
    DS_CHECK(expect_list(&list, expected, 5));
    SeqListInit(&empty);
    reverse_sequential_list(&empty);
    DS_CHECK(empty.length == 0);
}

DS_TEST_FUNCTION(erase_value) {
    const int input[] = {4, 2, 4, 1, 4};
    const int expected[] = {2, 1};
    SeqList first = make_list(input, 5);
    SeqList second = make_list(input, 5);
    erase_value_by_compaction(&first, 4);
    DS_CHECK(expect_list(&first, expected, 2));
    erase_value_by_counting(&second, 4);
    DS_CHECK(expect_list(&second, expected, 2));
    erase_value_by_counting(&second, 99);
    DS_CHECK(expect_list(&second, expected, 2));
}

DS_TEST_FUNCTION(delete_same_sequence) {
    const int input[] = {1, 2, 2, 2, 4, 4, 7};
    const int expected[] = {1, 2, 4, 7};
    SeqList list = make_list(input, 7);
    SeqList empty = {0};
    DS_CHECK(erase_sorted_duplicates(&list));
    DS_CHECK(expect_list(&list, expected, 4));
    SeqListInit(&empty);
    DS_CHECK(!erase_sorted_duplicates(&empty));
}

DS_TEST_FUNCTION(erase_range) {
    const int input[] = {1, 3, 5, 7, 9};
    const int expected[] = {1, 9};
    const int singleton_input[] = {4, 5, 6};
    const int singleton_expected[] = {4, 6};
    SeqList list = make_list(input, 5);
    SeqList singleton = make_list(singleton_input, 3);
    DS_CHECK(erase_closed_value_range(&list, 3, 7));
    DS_CHECK(expect_list(&list, expected, 2));
    DS_CHECK(erase_closed_value_range(&singleton, 5, 5));
    DS_CHECK(expect_list(&singleton, singleton_expected, 2));
    DS_CHECK(!erase_closed_value_range(&list, 9, 3));
}

DS_TEST_FUNCTION(merge_sequence) {
    const int left_input[] = {1, 3, 5};
    const int right_input[] = {2, 4, 6};
    const int expected[] = {1, 2, 3, 4, 5, 6};
    SeqList left = make_list(left_input, 3);
    SeqList right = make_list(right_input, 3);
    SeqList output = {0};
    SeqList too_large_left = {0}, too_large_right = {0};
    DS_CHECK(merge_sorted_lists(&left, &right, &output));
    DS_CHECK(expect_list(&output, expected, 6));
    too_large_left.length = 26;
    too_large_right.length = 25;
    DS_CHECK(!merge_sorted_lists(&too_large_left, &too_large_right, &output));
}

DS_TEST_FUNCTION(reverse_blocks) {
    int segment[] = {0, 1, 2, 3, 4};
    int expected_segment[] = {0, 3, 2, 1, 4};
    int blocks[] = {1, 2, 3, 4, 5};
    int expected_blocks[] = {3, 4, 5, 1, 2};
    reverse_segment(segment, 5, 1, 3);
    DS_CHECK(segment[0] == expected_segment[0] && segment[1] == expected_segment[1] &&
             segment[2] == expected_segment[2] && segment[3] == expected_segment[3] &&
             segment[4] == expected_segment[4]);
    reverse_segment(segment, 5, 3, 7);
    DS_CHECK(segment[1] == expected_segment[1]);
    exchange_adjacent_blocks(blocks, 5, 2);
    DS_CHECK(blocks[0] == expected_blocks[0] && blocks[1] == expected_blocks[1] &&
             blocks[2] == expected_blocks[2] && blocks[3] == expected_blocks[3] &&
             blocks[4] == expected_blocks[4]);
    exchange_adjacent_blocks(blocks, 5, 8);
    DS_CHECK(blocks[0] == expected_blocks[0]);
}

DS_TEST_FUNCTION(search_exchange_insert) {
    int values[5] = {1, 3, 5, 7, 0};
    size_t length = 4;
    int missing[5] = {1, 3, 5, 7};
    size_t missing_length = 4;
    int empty[1] = {0};
    size_t empty_length = 0;
    DS_CHECK(search_exchange_insert(values, &length, 5, 5) == 1);
    DS_CHECK(values[0] == 1 && values[1] == 3 && values[2] == 7 && values[3] == 5);
    DS_CHECK(search_exchange_insert(missing, &missing_length, 5, 4) == 0);
    DS_CHECK(missing_length == 5 && missing[0] == 1 && missing[1] == 3 &&
             missing[2] == 4 && missing[3] == 5 && missing[4] == 7);
    DS_CHECK(search_exchange_insert(empty, &empty_length, 1, 2) == 0);
    DS_CHECK(empty_length == 1 && empty[0] == 2);
    DS_CHECK(search_exchange_insert(empty, &empty_length, 1, 9) == -1);
}

DS_TEST_FUNCTION(common_three) {
    const int a[] = {1, 2, 2, 4, 7};
    const int b[] = {0, 2, 2, 5, 7};
    const int c[] = {2, 2, 3, 7};
    const int expected[] = {2, 7};
    const int no_match_a[] = {1}, no_match_b[] = {2}, no_match_c[] = {3};
    const int repeated[] = {4, 4, 4};
    int common[5], one_common[1];
    size_t count = 0;
    DS_CHECK(common_values_in_three_sorted_arrays(a, 5, b, 5, c, 4,
                                                  common, 5, &count));
    DS_CHECK(count == 2 && common[0] == expected[0] && common[1] == expected[1]);
    DS_CHECK(common_values_in_three_sorted_arrays(no_match_a, 1, no_match_b, 1,
                                                  no_match_c, 1, common, 5, &count));
    DS_CHECK(count == 0);
    DS_CHECK(common_values_in_three_sorted_arrays(repeated, 3, repeated, 3,
                                                  repeated, 3, one_common, 1, &count));
    DS_CHECK(count == 1 && one_common[0] == 4);
}

DS_TEST_FUNCTION(rotate_left) {
    int values[] = {1, 2, 3, 4, 5};
    int empty[1] = {0};
    rotate_left_by_reversal(values, 5, 2);
    DS_CHECK(values[0] == 3 && values[4] == 2);
    rotate_left_by_reversal(values, 5, 5);
    DS_CHECK(values[0] == 3 && values[4] == 2);
    rotate_left_by_reversal(values, 5, 12);
    DS_CHECK(values[0] == 5 && values[4] == 4);
    rotate_left_by_reversal(NULL, 0, 9);
    DS_CHECK(empty[0] == 0);
}

DS_TEST_FUNCTION(median_two_sorted) {
    const int a[] = {1, 3, 5}, b[] = {2, 4, 6}, one_a[] = {1}, one_b[] = {2};
    const int mismatch[] = {1, 2};
    int median = 0;
    DS_CHECK(median_of_two_equal_sorted_arrays(a, 3, b, 3, &median) && median == 3);
    DS_CHECK(median_of_two_equal_sorted_arrays(one_a, 1, one_b, 1, &median) && median == 1);
    DS_CHECK(!median_of_two_equal_sorted_arrays(NULL, 0, NULL, 0, &median));
    DS_CHECK(!median_of_two_equal_sorted_arrays(one_a, 1, mismatch, 2, &median));
}

DS_TEST_FUNCTION(majority) {
    const int values[] = {2, 2, 1, 2, 3, 2, 2};
    const int no_majority[] = {1, 2, 3, 2};
    int result = 0;
    DS_CHECK(majority_element(values, 7, &result) && result == 2);
    DS_CHECK(!majority_element(no_majority, 4, &result));
    DS_CHECK(!majority_element(NULL, 0, &result));
}

DS_TEST_FUNCTION(missing_positive) {
    const int a[] = {1, 2, 0};
    const int b[] = {3, 4, -1, 1};
    const int c[] = {1, 2, 3};
    DS_CHECK(smallest_missing_positive(a, 3) == 3);
    DS_CHECK(smallest_missing_positive(b, 4) == 2);
    DS_CHECK(smallest_missing_positive(c, 3) == 4);
    DS_CHECK(smallest_missing_positive(NULL, 0) == 1);
}

DS_TEST_FUNCTION(minimum_three_distance) {
    const int a[] = {-1, 0, 4}, b[] = {1, 2, 6}, c[] = {3, 5, 8};
    const int singleton[] = {1}, two[] = {2};
    DS_CHECK(minimum_three_array_distance(a, 3, b, 3, c, 3) == 4);
    DS_CHECK(minimum_three_array_distance(NULL, 0, singleton, 1, two, 1) == 0);
}

DS_TEST_FUNCTION(suffix_extreme_product) {
    const int values[] = {-2, -5, 3, -1};
    const long long expected[] = {10, 25, 9, 1};
    long long output[4];
    multiply_by_suffix_extreme(values, 4, output);
    DS_CHECK(output[0] == expected[0] && output[1] == expected[1] &&
             output[2] == expected[2] && output[3] == expected[3]);
    multiply_by_suffix_extreme(NULL, 0, NULL);
    DS_CHECK(output[3] == 1);
}

int main(int argc, char **argv) {
    const DsTestCase cases[] = {
        DS_TEST_CASE(delete_minimum), DS_TEST_CASE(reverse_sequence),
        DS_TEST_CASE(erase_value), DS_TEST_CASE(delete_same_sequence),
        DS_TEST_CASE(erase_range), DS_TEST_CASE(merge_sequence),
        DS_TEST_CASE(reverse_blocks), DS_TEST_CASE(search_exchange_insert),
        DS_TEST_CASE(common_three), DS_TEST_CASE(rotate_left),
        DS_TEST_CASE(median_two_sorted), DS_TEST_CASE(majority),
        DS_TEST_CASE(missing_positive), DS_TEST_CASE(minimum_three_distance),
        DS_TEST_CASE(suffix_extreme_product),
    };
    return ds_test_run(argc, argv, cases, sizeof(cases) / sizeof(cases[0]));
}
