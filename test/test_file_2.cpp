//
// Created by chenh on 5/16/2020.
//
// include any necessary headers
#include "matrix_implementation.h"
#include "test_assert.h"

// Test Tool declarations
#include <iostream>
using namespace std;
typedef int (*TestFunc)();
enum { PASS, FAILURE };


// test declarations
static int test0();
static int test1();
static int test2();


//  global variable (static)
Matrix<int> matrix;


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

static void after() {
    // executed after every test
    matrix = Matrix<int>();
}

void test_file_2_main() {
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
    // test sum
    assertTrue(matrix.sum() == 21)
    return PASS;
}

static int test1() {
    // test max
    assertTrue(matrix.max() == 6)
    return PASS;
}

static int test2() {
    // test min
    assertTrue(matrix.min() == 1)
    return PASS;
}

