//
// Created by chenh on 5/11/2020.
// Operator tests
//

// include any necessary headers
#include "matrix.h"

// Test Tool declarations
#include "test_assert.h"
#include <iostream>
using namespace std;
typedef int (*TestFunc)();
enum { PASS, FAILURE };


// test declarations
static int test0();
static int test1();
static int test2();


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
