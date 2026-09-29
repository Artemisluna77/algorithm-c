#include "complexity_examples.h"
#include "test_harness.h"

DS_TEST_FUNCTION(additive_blocks) {
    DS_CHECK(additive_block_work(0) == 1);
    DS_CHECK(additive_block_work(3) == 13);
}

DS_TEST_FUNCTION(multiplicative_blocks) {
    DS_CHECK(multiplicative_block_work(0) == 1);
    DS_CHECK(multiplicative_block_work(3) == 28);
}

DS_TEST_FUNCTION(summary_doubling) {
    DS_CHECK(summary_doubling_loop(0) == 1);
    DS_CHECK(summary_doubling_loop(8) == 16);
    DS_CHECK(summary_doubling_loop(1 << 30) == 2147483648LL);
}

DS_TEST_FUNCTION(summary_square_root) {
    DS_CHECK(summary_square_root_loop(25) == 5);
    DS_CHECK(summary_square_root_loop(26) == 5);
    DS_CHECK(summary_square_root_loop(36) == 5);
}

int main(int argc, char **argv) {
    const DsTestCase cases[] = {
        DS_TEST_CASE(additive_blocks),
        DS_TEST_CASE(multiplicative_blocks),
        DS_TEST_CASE(summary_doubling),
        DS_TEST_CASE(summary_square_root),
    };
    return ds_test_run(argc, argv, cases, sizeof(cases) / sizeof(cases[0]));
}
