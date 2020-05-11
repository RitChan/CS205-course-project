//
// Created by chenh on 5/11/2020.
//
// include any necessary headers
#include "matrix.h"

/* -- Test Tool declaration --- */
#include <iostream>
#include "test_assert.h"
using namespace std;
typedef int (*TestFunc)();
enum { PASS = 0, FAILURE = -1 };

// test declaration
static int test0();
static int test1();

//  global variable (make it static)
static Matrix<int> matrix;

static void before() {
    matrix = Matrix<int>();
    // executed before every test
}

static void after() {
    // executed after every test
}

void test_file_0_main() {
    TestFunc tests[] = {
            // all TestFunc registered here
            test0,
            test1
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
    // test Matrix(int, int) and Matrix.at(int)
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

static int test1() {
    // test matrix.at(i, j)

    return PASS;
}

