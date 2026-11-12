#include "linked_list_algorithms.h"
#include "test_harness.h"

#include <stdint.h>
#include <stdlib.h>

static SinglyLinkedList make_list(const int *values, size_t length, int with_header) {
    SinglyLinkedList list = {0};
    size_t i;
    SinglyLinkedListInit(&list, with_header != 0);
    for (i = 0; i < length; ++i) SinglyLinkedListAppend(&list, values[i]);
    return list;
}

static int expect_list(const SinglyLinkedList *list, const int *expected, size_t length) {
    LNode *node = SinglyLinkedListFirst(list);
    size_t i = 0;
    while (node != NULL && i < length) {
        if (node->data != expected[i]) return 0;
        ++i;
        node = node->next;
    }
    return node == NULL && i == length;
}

static int expect_circular(const CircularSinglyLinkedList *list, const int *expected, size_t length) {
    LNode *node;
    size_t i;
    if (list == NULL || list->head == NULL) return 0;
    node = list->head->next;
    for (i = 0; i < length; ++i) {
        if (node == list->head || node->data != expected[i]) return 0;
        node = node->next;
    }
    return node == list->head;
}

DS_TEST_FUNCTION(delete_value_methods) {
    const int input[] = {7, 1, 7, 7, 2, 7};
    const int expected[] = {1, 2};
    SinglyLinkedList first = make_list(input, 6, 1);
    SinglyLinkedList second = make_list(input, 6, 1);
    delete_all_value_by_predecessor(&first, 7);
    delete_all_value_by_tail_builder(&second, 7);
    DS_CHECK(expect_list(&first, expected, 2));
    DS_CHECK(expect_list(&second, expected, 2));
    SinglyLinkedListDestroy(&first);
    SinglyLinkedListDestroy(&second);
}

DS_TEST_FUNCTION(delete_minimum) {
    const int input[] = {4, 1, 1, 3}, expected[] = {4, 1, 3};
    SinglyLinkedList list = make_list(input, 4, 1);
    SinglyLinkedList empty = make_list(NULL, 0, 1);
    DS_CHECK(delete_minimum_node(&list));
    DS_CHECK(expect_list(&list, expected, 3));
    DS_CHECK(!delete_minimum_node(&empty));
    SinglyLinkedListDestroy(&list);
    SinglyLinkedListDestroy(&empty);
}

DS_TEST_FUNCTION(reverse_methods) {
    const int input[] = {1, 2, 3, 4}, expected[] = {4, 3, 2, 1}, singleton_value[] = {5};
    SinglyLinkedList first = make_list(input, 4, 1);
    SinglyLinkedList second = make_list(input, 4, 1);
    SinglyLinkedList empty = make_list(NULL, 0, 1);
    SinglyLinkedList singleton = make_list(singleton_value, 1, 1);
    reverse_by_head_insertion(&first);
    reverse_by_pointer_reversal(&second);
    reverse_by_pointer_reversal(&empty);
    reverse_by_head_insertion(&singleton);
    DS_CHECK(expect_list(&first, expected, 4));
    DS_CHECK(expect_list(&second, expected, 4));
    DS_CHECK(expect_list(&empty, NULL, 0));
    DS_CHECK(expect_list(&singleton, singleton_value, 1));
    SinglyLinkedListDestroy(&first);
    SinglyLinkedListDestroy(&second);
    SinglyLinkedListDestroy(&empty);
    SinglyLinkedListDestroy(&singleton);
}

DS_TEST_FUNCTION(delete_open_range) {
    const int input[] = {1, 2, 3, 4, 5, 3}, expected[] = {1, 2, 5};
    SinglyLinkedList list = make_list(input, 6, 1);
    DS_CHECK(delete_open_value_range(&list, 2, 5) == 3);
    DS_CHECK(expect_list(&list, expected, 3));
    DS_CHECK(delete_open_value_range(&list, 5, 2) == 0);
    DS_CHECK(expect_list(&list, expected, 3));
    SinglyLinkedListDestroy(&list);
}

DS_TEST_FUNCTION(split_alternating_positions) {
    const int input[] = {10, 20, 30, 40, 50};
    const int expected_odd[] = {10, 30, 50}, expected_even[] = {40, 20};
    SinglyLinkedList source = make_list(input, 5, 1);
    SinglyLinkedList odd = {0}, even = {0};
    DS_CHECK(!split_alternating_positions(&source, &source, &even));
    DS_CHECK(!split_alternating_positions(&source, &odd, &odd));
    DS_CHECK(odd.head == NULL && even.head == NULL);
    DS_CHECK(expect_list(&source, input, 5));
    DS_CHECK(split_alternating_positions(&source, &odd, &even));
    DS_CHECK(expect_list(&odd, expected_odd, 3));
    DS_CHECK(expect_list(&even, expected_even, 2));
    DS_CHECK(expect_list(&source, input, 5));
    SinglyLinkedListDestroy(&source);
    SinglyLinkedListDestroy(&odd);
    SinglyLinkedListDestroy(&even);
}

DS_TEST_FUNCTION(erase_adjacent_duplicates) {
    const int input[] = {1, 1, 1, 3, 4, 4, 8}, expected[] = {1, 3, 4, 8};
    SinglyLinkedList list = make_list(input, 7, 1);
    DS_CHECK(erase_adjacent_duplicates(&list) == 3);
    DS_CHECK(expect_list(&list, expected, 4));
    SinglyLinkedListDestroy(&list);
}

DS_TEST_FUNCTION(sorted_intersections) {
    const int left_values[] = {1, 2, 2, 4, 7}, right_values[] = {2, 2, 3, 7, 9};
    const int common_values[] = {2, 2, 7}, unchanged_left[] = {1, 2, 2, 4, 7};
    const int unchanged_right[] = {2, 2, 3, 7, 9}, self_values[] = {1, 2, 2, 4};
    SinglyLinkedList left = make_list(left_values, 5, 1);
    SinglyLinkedList right = make_list(right_values, 5, 1);
    SinglyLinkedList common = {0};
    SinglyLinkedList destructive_left = make_list(left_values, 5, 1);
    SinglyLinkedList destructive_right = make_list(right_values, 5, 1);
    SinglyLinkedList self = make_list(self_values, 4, 1);
    DS_CHECK(!common_values_sorted_lists(&left, &right, &left));
    DS_CHECK(!common_values_sorted_lists(&left, &right, &right));
    DS_CHECK(expect_list(&left, unchanged_left, 5));
    DS_CHECK(expect_list(&right, unchanged_right, 5));
    DS_CHECK(common_values_sorted_lists(&left, &right, &common));
    DS_CHECK(expect_list(&common, common_values, 3));
    DS_CHECK(expect_list(&left, unchanged_left, 5));
    DS_CHECK(expect_list(&right, unchanged_right, 5));
    intersection_by_source_union_algorithm(&destructive_left, &destructive_right);
    DS_CHECK(expect_list(&destructive_left, common_values, 3));
    DS_CHECK(expect_list(&destructive_right, NULL, 0));
    intersection_by_source_union_algorithm(&self, &self);
    DS_CHECK(expect_list(&self, self_values, 4));
    SinglyLinkedListDestroy(&left);
    SinglyLinkedListDestroy(&right);
    SinglyLinkedListDestroy(&common);
    SinglyLinkedListDestroy(&destructive_left);
    SinglyLinkedListDestroy(&destructive_right);
    SinglyLinkedListDestroy(&self);
}

DS_TEST_FUNCTION(contiguous_pattern) {
    const int text_values[] = {1, 2, 3, 4, 3}, pattern_values[] = {2, 3, 4}, absent_values[] = {2, 4};
    SinglyLinkedList text = make_list(text_values, 5, 1);
    SinglyLinkedList pattern = make_list(pattern_values, 3, 1);
    SinglyLinkedList absent = make_list(absent_values, 2, 1);
    SinglyLinkedList empty = make_list(NULL, 0, 1);
    DS_CHECK(contains_contiguous_list(&text, &pattern));
    DS_CHECK(!contains_contiguous_list(&text, &absent));
    DS_CHECK(contains_contiguous_list(&text, &empty));
    SinglyLinkedListDestroy(&text);
    SinglyLinkedListDestroy(&pattern);
    SinglyLinkedListDestroy(&absent);
    SinglyLinkedListDestroy(&empty);
}

DS_TEST_FUNCTION(circular_singly_link) {
    const int expected[] = {1, 2, 3, 4};
    CircularSinglyLinkedList first = {0}, second = {0}, empty = {0};
    DS_CHECK(CircularSinglyLinkedListInit(&first));
    DS_CHECK(CircularSinglyLinkedListInit(&second));
    DS_CHECK(CircularSinglyLinkedListInit(&empty));
    DS_CHECK(CircularSinglyLinkedListAppend(&first, 1));
    DS_CHECK(CircularSinglyLinkedListAppend(&first, 2));
    DS_CHECK(CircularSinglyLinkedListAppend(&second, 3));
    DS_CHECK(CircularSinglyLinkedListAppend(&second, 4));
    Link(&first, &second);
    DS_CHECK(expect_circular(&first, expected, 4));
    DS_CHECK(CircularSinglyLinkedListEmpty(&second));
    Link(&first, &empty);
    DS_CHECK(expect_circular(&first, expected, 4));
    CircularSinglyLinkedListDestroy(&first);
    CircularSinglyLinkedListDestroy(&second);
    CircularSinglyLinkedListDestroy(&empty);
}

DS_TEST_FUNCTION(circular_doubly_symmetry) {
    const int even_values[] = {1, 2, 2, 1}, odd_values[] = {1, 2, 1};
    CircularDoublyLinkedList even = {0}, odd = {0}, empty = {0};
    size_t i;
    DS_CHECK(CircularDoublyLinkedListInit(&even));
    DS_CHECK(CircularDoublyLinkedListInit(&odd));
    DS_CHECK(CircularDoublyLinkedListInit(&empty));
    for (i = 0; i < 4; ++i) DS_CHECK(CircularDoublyLinkedListAppend(&even, even_values[i]));
    for (i = 0; i < 3; ++i) DS_CHECK(CircularDoublyLinkedListAppend(&odd, odd_values[i]));
    DS_CHECK(Symmetry(&even));
    DS_CHECK(Symmetry(&odd));
    DS_CHECK(CircularDoublyLinkedListAppend(&odd, 9));
    DS_CHECK(!Symmetry(&odd));
    DS_CHECK(Symmetry(&empty));
    CircularDoublyLinkedListDestroy(&even);
    CircularDoublyLinkedListDestroy(&odd);
    CircularDoublyLinkedListDestroy(&empty);
}

static int frequency_entries_equal(const FrequencyList *list, const int *values,
                                   const size_t *frequencies, size_t length) {
    FrequencyNode *node;
    size_t i = 0;
    if (list == NULL || list->head == NULL) return 0;
    for (node = list->head->next; node != NULL && i < length; node = node->next, ++i) {
        if (node->data != values[i] || node->frequency != frequencies[i]) return 0;
    }
    return node == NULL && i == length;
}

DS_TEST_FUNCTION(frequency_locate) {
    const int after_30_values[] = {10, 20, 30}, after_20_values[] = {20, 10, 30};
    const size_t after_30_freq[] = {3, 2, 1}, after_20_freq[] = {3, 3, 1};
    FrequencyList list = {0};
    FrequencyList saturated_list = {0};
    FrequencyNode *accessed;
    FrequencyNode *saturated;
    DS_CHECK(FrequencyListInit(&list));
    DS_CHECK(FrequencyListAppend(&list, 10, 3) != NULL);
    DS_CHECK(FrequencyListAppend(&list, 20, 2) != NULL);
    DS_CHECK(FrequencyListAppend(&list, 30, 0) != NULL);
    accessed = Locate(&list, 30);
    DS_CHECK(accessed != NULL && accessed->frequency == 1);
    DS_CHECK(frequency_entries_equal(&list, after_30_values, after_30_freq, 3));
    DS_CHECK(Locate(&list, 99) == NULL);
    accessed = Locate(&list, 20);
    DS_CHECK(accessed != NULL && accessed->frequency == 3);
    DS_CHECK(frequency_entries_equal(&list, after_20_values, after_20_freq, 3));
    FrequencyListDestroy(&list);

    DS_CHECK(FrequencyListInit(&saturated_list));
    saturated = FrequencyListAppend(&saturated_list, 77, SIZE_MAX);
    DS_CHECK(saturated != NULL);
    DS_CHECK(Locate(&saturated_list, 77) == saturated);
    DS_CHECK(saturated->frequency == SIZE_MAX);
    DS_CHECK(saturated_list.head->next == saturated && saturated->next == NULL);
    FrequencyListDestroy(&saturated_list);
}

DS_TEST_FUNCTION(rotate_right) {
    const int input[] = {1, 2, 3, 4, 5};
    const int after_two[] = {4, 5, 1, 2, 3}, after_seven[] = {2, 3, 4, 5, 1};
    const int headless_input[] = {1, 2, 3, 4}, headless_expected[] = {4, 1, 2, 3};
    SinglyLinkedList list = make_list(input, 5, 1);
    SinglyLinkedList without_header = make_list(headless_input, 4, 0);
    rotate_right_by_k(&list, 2);
    DS_CHECK(expect_list(&list, after_two, 5));
    rotate_right_by_k(&list, 12);
    DS_CHECK(expect_list(&list, after_seven, 5));
    rotate_right_by_k(&list, 5);
    DS_CHECK(expect_list(&list, after_seven, 5));
    rotate_right_by_k(&without_header, 1);
    DS_CHECK(expect_list(&without_header, headless_expected, 4));
    SinglyLinkedListDestroy(&list);
    SinglyLinkedListDestroy(&without_header);
}

DS_TEST_FUNCTION(symmetric_pair_sum) {
    const int input[] = {1, 9, 2, 8, 3, 7}, odd_values[] = {1, 2, 3};
    const int headless_values[] = {5, 1, 4, 3};
    SinglyLinkedList list = make_list(input, 6, 1);
    SinglyLinkedList odd = make_list(odd_values, 3, 1);
    SinglyLinkedList without_header = make_list(headless_values, 4, 0);
    long long maximum = 0;
    DS_CHECK(maximum_symmetric_pair_sum(&list, &maximum) && maximum == 12);
    DS_CHECK(expect_list(&list, input, 6));
    DS_CHECK(!maximum_symmetric_pair_sum(&odd, &maximum));
    DS_CHECK(maximum_symmetric_pair_sum(&without_header, &maximum) && maximum == 8);
    DS_CHECK(expect_list(&without_header, headless_values, 4));
    SinglyLinkedListDestroy(&list);
    SinglyLinkedListDestroy(&odd);
    SinglyLinkedListDestroy(&without_header);
}

DS_TEST_FUNCTION(find_loop_start) {
    LNode third = {3, NULL}, second = {2, &third}, first = {1, &second};
    DS_CHECK(find_loop_start(&first) == NULL);
    third.next = &second;
    DS_CHECK(find_loop_start(&first) == &second);
    DS_CHECK(find_loop_start(NULL) == NULL);
}

DS_TEST_FUNCTION(kth_from_end) {
    Q17Node head = {0, NULL};
    Q17Node first = {11, NULL}, second = {22, NULL}, third = {33, NULL}, fourth = {44, NULL};
    Q17Node empty_header = {0, NULL};
    int value = 0;
    head.link = &first;
    first.link = &second;
    second.link = &third;
    third.link = &fourth;
    DS_CHECK(kth_from_end(&head, 1, &value) && value == 44);
    DS_CHECK(kth_from_end(&head, 3, &value) && value == 22);
    DS_CHECK(!kth_from_end(&head, 0, &value));
    DS_CHECK(!kth_from_end(&head, 5, &value));
    DS_CHECK(!kth_from_end(&empty_header, 1, &value));
}

DS_TEST_FUNCTION(common_suffix) {
    Q18Node shared_tail = {'g', NULL}, shared_head = {'i', &shared_tail};
    Q18Node first_data = {'d', &shared_head}, second_prefix2 = {'n', &shared_head};
    Q18Node second_prefix1 = {'e', &second_prefix2};
    Q18Node first_header = {'\0', &first_data}, second_header = {'\0', &second_prefix1};
    Q18Node disjoint_data = {'x', NULL}, disjoint_header = {'\0', &disjoint_data};
    DS_CHECK(singly_list_length(&first_header) == 3);
    DS_CHECK(singly_list_length(NULL) == 0);
    DS_CHECK(find_common_suffix_start(&first_header, &second_header) == &shared_head);
    DS_CHECK(find_common_suffix_start(&first_header, &disjoint_header) == NULL);
}

DS_TEST_FUNCTION(absolute_value_deduplication) {
    const int expected[] = {21, -15, -21, 0, -2};
    Q19Node *head = (Q19Node *)calloc(1, sizeof(Q19Node));
    Q19Node *tail = head;
    const int values[] = {21, -15, 15, -21, 0, 0, -2, 2};
    size_t i, index = 0;
    DS_CHECK(head != NULL);
    if (head == NULL) return;
    for (i = 0; i < 8; ++i) {
        tail->link = (Q19Node *)malloc(sizeof(Q19Node));
        if (tail->link == NULL) break;
        tail = tail->link;
        tail->data = values[i];
        tail->link = NULL;
    }
    DS_CHECK(i == 8);
    DS_CHECK(remove_duplicate_absolute_values(head, 20) == 3);
    for (tail = head->link; tail != NULL; tail = tail->link) {
        if (index >= 5 || tail->data != expected[index]) DS_CHECK(0);
        ++index;
    }
    DS_CHECK(index == 5);
    tail = head;
    while (tail != NULL) {
        Q19Node *next = tail->link;
        free(tail);
        tail = next;
    }
    DS_CHECK(remove_duplicate_absolute_values(NULL, 20) == 0);
}

DS_TEST_FUNCTION(reorder_first_last) {
    const int input[] = {1, 2, 3, 4, 5, 6}, expected[] = {1, 6, 2, 5, 3, 4};
    const int short_input[] = {1, 2}, odd_input[] = {1, 2, 3, 4, 5}, odd_expected[] = {1, 5, 2, 4, 3};
    SinglyLinkedList list = make_list(input, 6, 1);
    SinglyLinkedList short_list = make_list(short_input, 2, 1);
    SinglyLinkedList odd_list = make_list(odd_input, 5, 1);
    reorder_first_last(&list);
    DS_CHECK(expect_list(&list, expected, 6));
    reorder_first_last(&short_list);
    DS_CHECK(expect_list(&short_list, short_input, 2));
    reorder_first_last(&odd_list);
    DS_CHECK(expect_list(&odd_list, odd_expected, 5));
    SinglyLinkedListDestroy(&list);
    SinglyLinkedListDestroy(&short_list);
    SinglyLinkedListDestroy(&odd_list);
}

int main(int argc, char **argv) {
    const DsTestCase cases[] = {
        DS_TEST_CASE(delete_value_methods), DS_TEST_CASE(delete_minimum),
        DS_TEST_CASE(reverse_methods), DS_TEST_CASE(delete_open_range),
        DS_TEST_CASE(split_alternating_positions), DS_TEST_CASE(erase_adjacent_duplicates),
        DS_TEST_CASE(sorted_intersections), DS_TEST_CASE(contiguous_pattern),
        DS_TEST_CASE(circular_singly_link), DS_TEST_CASE(circular_doubly_symmetry),
        DS_TEST_CASE(frequency_locate), DS_TEST_CASE(rotate_right),
        DS_TEST_CASE(symmetric_pair_sum), DS_TEST_CASE(find_loop_start),
        DS_TEST_CASE(kth_from_end), DS_TEST_CASE(common_suffix),
        DS_TEST_CASE(absolute_value_deduplication), DS_TEST_CASE(reorder_first_last),
    };
    return ds_test_run(argc, argv, cases, sizeof(cases) / sizeof(cases[0]));
}
