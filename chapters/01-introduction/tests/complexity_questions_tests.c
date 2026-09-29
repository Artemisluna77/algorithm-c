#include "complexity_questions.h"
#include "test_harness.h"

#include <stdlib.h>

DS_TEST_FUNCTION(q06) {
    DS_CHECK(q06_final_power_of_two(0) == 1);
    DS_CHECK(q06_final_power_of_two(8) == 16);
    DS_CHECK(q06_final_power_of_two(1 << 30) == 2147483648LL);
}

DS_TEST_FUNCTION(q07) {
    DS_CHECK(q07_first_cube_over_n(0) == 1);
    DS_CHECK(q07_first_cube_over_n(8) == 3);
}

DS_TEST_FUNCTION(q08) {
    DS_CHECK(q08_worst_case_bubble_swaps(0) == 0);
    DS_CHECK(q08_worst_case_bubble_swaps(2) == 0);
    DS_CHECK(q08_worst_case_bubble_swaps(5) == 6);
}

DS_TEST_FUNCTION(q09) {
    DS_CHECK(q09_print_count(-2) == 0);
    DS_CHECK(q09_print_count(0) == 0);
    DS_CHECK(q09_print_count(3) == 9);
}

DS_TEST_FUNCTION(q10) {
    DS_CHECK(q10_increment_count(0) == 0);
    DS_CHECK(q10_increment_count(3) == 12);
}

DS_TEST_FUNCTION(q11) {
    long long result = 0;
    DS_CHECK(q11_recursive_recurrence(1, &result) && result == 1);
    DS_CHECK(q11_recursive_recurrence(4, &result) && result == 12);
    DS_CHECK(!q11_recursive_recurrence(0, &result));
    DS_CHECK(!q11_recursive_recurrence(2, NULL));
}

DS_TEST_FUNCTION(q12) {
    DS_CHECK(q12_final_doubled_value(0) == 2);
    DS_CHECK(q12_final_doubled_value(10) == 8);
}

DS_TEST_FUNCTION(q13) {
    long long result = 0;
    DS_CHECK(q13_factorial(0, &result) && result == 1);
    DS_CHECK(q13_factorial(5, &result) && result == 120);
    DS_CHECK(q13_factorial(20, &result) && result == 2432902008176640000LL);
    DS_CHECK(!q13_factorial(21, &result));
    DS_CHECK(!q13_factorial(-1, &result));
    DS_CHECK(!q13_factorial(5, NULL));
}

DS_TEST_FUNCTION(q14) {
    DS_CHECK(q14_nested_loop_count(0) == 0);
    DS_CHECK(q14_nested_loop_count(5) == 15);
}

DS_TEST_FUNCTION(q15) {
    DS_CHECK(q15_triangular_sum_iterations(-1) == 0);
    DS_CHECK(q15_triangular_sum_iterations(0) == 0);
    DS_CHECK(q15_triangular_sum_iterations(10) == 4);
}

DS_TEST_FUNCTION(q16) {
    DS_CHECK(q16_integer_square_root(0) == 0);
    DS_CHECK(q16_integer_square_root(15) == 3);
    DS_CHECK(q16_integer_square_root(16) == 4);
}

DS_TEST_FUNCTION(q17) {
    DS_CHECK(q17_geometric_nested_count(0) == 0);
    DS_CHECK(q17_geometric_nested_count(8) == 7);
}

DS_TEST_FUNCTION(q18) {
    DS_CHECK(q18_triangular_count(0) == 0);
    DS_CHECK(q18_triangular_count(9) == 6);
}

DS_TEST_FUNCTION(application_01) {
    DS_CHECK(application_01_linear_accumulation(0) == 0);
    DS_CHECK(application_01_linear_accumulation(5) == 60);
}

DS_TEST_FUNCTION(application_02) {
    DS_CHECK(application_02_integer_square_root(0) == 0);
    DS_CHECK(application_02_integer_square_root(26) == 5);
}

DS_TEST_FUNCTION(application_03) {
    int *matrix = NULL;
    DS_CHECK(application_03_zero_matrix(2, 3, &matrix));
    DS_CHECK(matrix != NULL);
    if (matrix != NULL) {
        size_t i;
        for (i = 0; i < 6; ++i) DS_CHECK(matrix[i] == 0);
        free(matrix);
    }
    matrix = NULL;
    DS_CHECK(application_03_zero_matrix(0, 3, &matrix));
    DS_CHECK(matrix == NULL);
    DS_CHECK(!application_03_zero_matrix(2, 3, NULL));
}

int main(int argc, char **argv) {
    const DsTestCase cases[] = {
        DS_TEST_CASE(q06), DS_TEST_CASE(q07), DS_TEST_CASE(q08),
        DS_TEST_CASE(q09), DS_TEST_CASE(q10), DS_TEST_CASE(q11),
        DS_TEST_CASE(q12), DS_TEST_CASE(q13), DS_TEST_CASE(q14),
        DS_TEST_CASE(q15), DS_TEST_CASE(q16), DS_TEST_CASE(q17),
        DS_TEST_CASE(q18), DS_TEST_CASE(application_01),
        DS_TEST_CASE(application_02), DS_TEST_CASE(application_03),
    };
    return ds_test_run(argc, argv, cases, sizeof(cases) / sizeof(cases[0]));
}
