add_ds_test_executable(ch04_string_tests
        tests/string_tests.c
        body/string_matching.c
)
target_include_directories(ch04_string_tests PRIVATE body)

foreach(CASE_NAME IN ITEMS storage_types brute_force_match kmp_next_table kmp_match
        kmp_overlap nextval_table optimized_kmp_match)
    add_ds_test_case(ch04_string_tests ${CASE_NAME})
endforeach()
