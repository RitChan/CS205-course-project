/**
 * @file test_file_2.cpp
 * @ingroup test
 * @brief Sum, Max, Min tests.
 */

// include any necessary headers
#include "matrix_implementation.h"
#include "test_assert.h"

// Test Tool declarations
#include "preset.h"


/** @name Test Declarations */
/** @{ */
static int test0();
static int test1();
static int test2();
static int test3();
static int test4();
static int test5();
static int test6();
static int test7();
static int test8();
/** @} */


/** @name Global Variables */
/** @{ */
Matrix<int> matrix; /**< global matrix variable*/
/** @} */


/** Execute before every test. */
static void before() {
    // executed before every test
    matrix = Matrix<int>(2, 3);
    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[0][2] = 3;
    matrix[1][0] = 4;
    matrix[1][1] = 5;
    matrix[1][2] = 6;
}

/** Execute after every test. */
static void after() {
    // executed after every test
    matrix = Matrix<int>();
}

void test_file_2_main() {
    TestFunc tests[] = {
            // all TestFunc registered here
            test0,
            test1,
            test2,
            test3,
            test4,
            test5,
            test6,
            test7,
            test8,
    };
    int i = 0, ret;
    for (TestFunc test: tests) {
        before();
        ret = (*test)();
        after();
        if (ret != PASS)
            cout << "Test " << i << " failed" << endl;
        else
            cout << "Test " << i << " passed" << endl;
        i += 1;
    }
}

/**
 * Test sum.
 */
static int test0() {
    // test sum
    assertTrue(matrix.sum() == 21)
    return PASS;
}

/**
 * Test max.
 */
static int test1() {
    // test max
    assertTrue(matrix.max() == 6)
    return PASS;
}

/**
 * Test min.
 */
static int test2() {
    // test min
    assertTrue(matrix.min() == 1)
    return PASS;
}

/**
 * Test row_max.
 */
static int test3() {
    // test row_max
    assertTrue(matrix.row_max(0) == 3)
    assertTrue(matrix.row_max(1) == 6)
    return PASS;
}

/**
 * Test row_min.
 */
static int test4() {
    // test row_min
    assertTrue(matrix.row_min(0) == 1)
    assertTrue(matrix.row_min(1) == 4)
    return PASS;
}

/**
 * Test row_sum.
 */
static int test5() {
    // test row_sum
    assertTrue(matrix.row_sum(0) == 6)
    assertTrue(matrix.row_sum(1) == 15)
    return PASS;
}

/**
 * Test col_min.
 */
static int test6() {
    // test col_min
    assertTrue(matrix.col_min(0) == 1)
    assertTrue(matrix.col_min(2) == 3)
    return PASS;
}

/**
 * Test col_max.
 */
static int test7() {
    // test col_max
    assertTrue(matrix.col_max(0) == 4)
    assertTrue(matrix.col_max(1) == 5)
    return PASS;
}

/**
 * Test col_sum.
 */
static int test8() {
    // test col_sum
    assertTrue(matrix.col_sum(0) == 5)
    assertTrue(matrix.col_sum(2) == 9)
    return PASS;
}