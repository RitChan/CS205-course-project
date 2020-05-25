//
// Created by chenh on 5/11/2020.
// Operator tests
//

// include any necessary headers
#include "matrix_implementation.h"

// Test Tool declarations
#include "test_assert.h"
#include <iostream>
using namespace std;
typedef int (*TestFunc)();
enum { PASS = 0, FAILURE = -1 };


// test declarations
static int test0();
static int test1();
static int test2();
static int test3();
static int test4();
static int test5();
static int test6();
static int test7();
static int test8();


//  global variable
static Matrix<int> matrix;


static void before() {
    // executed before every test
    matrix = Matrix<int>(2, 2);
    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[1][0] = 3;
    matrix[1][1] = 4;
}

static void after() {
    // executed after every test
    matrix = Matrix<int>();
}

void test_file_1_main() {
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
            test8
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

static int test0() {
    // test scalar multiplication
    Matrix<int> matrix1 = 2 * matrix;
    Matrix<int> matrix2 = matrix * 2;
    assertTrue(matrix1[0][0] == 2)
    assertTrue(matrix1[1][1] == 8)
    assertTrue(matrix2[0][1] == 4)
    return PASS;
}

static int test1() {
    // test `matrix *= scalar`
    matrix *= 2;
    assertTrue(matrix[0][0] == 2)
    assertTrue(matrix[1][1] == 8)
    return PASS;
}

static int test2() {
    // test `matrix + matrix`
    Matrix<int> sum = matrix + matrix;
    assertTrue(sum.valid())
    assertTrue(sum[0][0] == 2)
    assertTrue(sum[1][0] == 6)

    Matrix<int> invalid_sum = Matrix<int>(1, 3) + matrix;
    assertTrue(!invalid_sum.valid())

    return PASS;
}

static int test3() {
    // test `matrix - matrix`
    Matrix<int> diff = matrix - matrix;
    assertTrue(diff.valid())
    assertTrue(diff[0][0] == 0)

    Matrix<int> matrix1(matrix.get_d1size(), matrix.get_d2size());
    diff = matrix1 - matrix;
    assertTrue(diff[0][0] == - matrix[0][0])

    matrix1 = Matrix<int>(1, 20);
    diff = matrix - matrix1;
    assertTrue(!diff.valid())

    return PASS;
}

static int test4() {
    // test `matrix / scalar`
    Matrix<int> res = matrix / 2;
    assertTrue(res[0][0] == 0)
    assertTrue(res[1][1] == 2)
    return PASS;
}

static int test5() {
    // test `Matrix::transpose`
    Matrix<double> matrix1(4, 5);
    matrix1 = matrix1.transpose();
    assertTrue(matrix1.valid())
    assertTrue(matrix1.get_d2size() == 4)
    assertTrue(matrix1.get_d1size() == 5)

    matrix = matrix.transpose();
    assertTrue(matrix[0][0] == 1)
    assertTrue(matrix[1][0] == 2)

    return PASS;
}

static int test6() {
    // test `matrix += matrix;
    Matrix<int> m(1, 10);
    assertTrue(!(matrix+=m).valid());

    matrix += matrix;
    assertTrue(matrix[0][0] == 2)
    assertTrue(matrix[1][0] == 6)

    return PASS;
}

static int test7() {
    // test `matrix * matrix`
    Matrix<int> other = matrix * matrix;
    assertTrue(other.valid());
    assertTrue(other.at(0, 0) == 7)
    assertTrue(other.at(1, 1) == 22)

    other = matrix * Matrix<int>(1, 10);
    assertTrue(!other.valid())

    other = matrix * Matrix<int>(2, 10);
    assertTrue(other.valid())
    assertTrue(other.get_d1size() == 2)
    assertTrue(other.get_d2size() == 10)

    return PASS;
}

static int test8() {
    // test matrix -= matrix
    Matrix<int> other = Matrix<int>(2, 2);

    other[0][1] = 5;
    other[1][0] = 2;

    assertTrue((matrix -= other).valid())
    assertTrue(matrix[0][1] == -3)
    assertTrue(matrix[1][0] == 1)

    assertTrue(!(matrix -= Matrix<int>(1, 10)).valid())

    return PASS;
}
