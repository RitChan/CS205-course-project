/**
 * @file test_header.h
 * @ingroup test
 * @brief Registers all test files to be executed.
 */

#ifndef COURSEPROJECT_TEST_HEADER_H
#define COURSEPROJECT_TEST_HEADER_H
typedef void (*TestFileFunc)();

/** @name Test File Main Functions */
/** @{ */

/** Run tests in test file 0 */
void test_file_0_main();

/** Run tests in test file 1 */
void test_file_1_main();

/** Run tests in test file 2 */
void test_file_2_main();

/** @} */

/**
 * All top file-level test functions registered here.
 */
TestFileFunc all[] = {
        test_file_0_main,
        test_file_1_main,
        test_file_2_main
};
#endif //COURSEPROJECT_TEST_HEADER_H
