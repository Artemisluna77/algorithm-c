#include "complexity_examples.h"
#include "test_harness.h"

DS_TEST_FUNCTION(reverse_search) {
    const int values[] = {4, 8, 15, 16};
    DS_CHECK(reverse_find(values, 4, 16) == 3);
    DS_CHECK(reverse_find(values, 4, 4) == 0);
    DS_CHECK(reverse_find(values, 4, 23) == -1);
    DS_CHECK(reverse_find(NULL, 0, 23) == -1);
}

int main(int argc, char **argv) {
    const DsTestCase cases[] = {DS_TEST_CASE(reverse_search)};
    return ds_test_run(argc, argv, cases, sizeof(cases) / sizeof(cases[0]));
}
