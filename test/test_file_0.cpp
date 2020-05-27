/**
 * @file test_file_0.cpp
 * @ingroup test
 * @brief Most basic functionality tests.
 */

// include any necessary headers
#include "matrix_implementation.h"

/* -- Test Tool declaration --- */
#include "preset.h"

/** @name Test Declarations */
/** @{ */
static int test0();
static int test1();
static int test2();
/** @} */

/** @name Global Variables */
/** @{ */
static Matrix<int> matrix; /**< global matrix variable*/
/** @} */

/** Execute before every test. */
static void before() {
    matrix = Matrix<int>();
}

/** Execute after every test. */
static void after() {

}

void test_file_0_main() {
    TestFunc tests[] = {
            // all TestFunc registered here
            test0,
            test1,
            test2
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
 * @brief Test Matrix(int, int) and Matrix.at(int)
 */
static int test0() {
    matrix = Matrix<int>(5, 6);
    assertTrue(matrix.get_d1size() == 5)
    assertTrue(matrix.get_d2size() == 6)
    expectException(matrix.at(5))
    expectException(matrix.at(-1))
    assertNoException(matrix.at(4))
    assertNoException(matrix.at(0))

    // triangle check
    matrix = Matrix<int>(10, 1);
    assertTrue(matrix.get_d1size() == 10)
    assertTrue(matrix.get_d2size() == 1)
    expectException(matrix.at(10))
    assertNoException(matrix.at(6))

    expectException(matrix.at(1).at(1))
    assertNoException(matrix.at(1).at(0));

    return PASS;
}

/**
 * @brief Test matrix.at(i, j)
 */
static int test1() {
    matrix = Matrix<int>(5, 6);
    expectException(matrix.at(5, 6))
    assertNoException(matrix.at(4, 5))
    assertTrue(matrix.at(4, 5) == 0)
    assertTrue((matrix.at(0, 0) = 1) == 1)
    return PASS;
}

/**
 * Test initializer_init constructor.
 */
static int test2() {
    Matrix<int> matrix1{
            {1, 2, 3},
            {4, 5, 6}
    };
    assertTrue(matrix1.valid())
    assertTrue(matrix1.get_d1size() == 2)
    assertTrue(matrix1.get_d2size() == 3)
    assertTrue(matrix1.at(0, 0) == 1)
    assertTrue(matrix1.at(1, 2) == 6)

    Matrix<int>matrix2{
            {}
    };
    assertTrue(!matrix2.valid())

    Matrix<int>matrix3{
            {1, 2},
            {0}
    };
    assertTrue(!matrix3.valid())

    return PASS;
}