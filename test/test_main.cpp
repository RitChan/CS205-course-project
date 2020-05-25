/**
 * @file test_main.cpp
 * @ingroup test
 * @brief Top level entry for all tests.
 */
#include "test_header.h"
#include <iostream>
using namespace std;

/**
 * Top level entry for all tests.
 */
int main() {
    int i = 0;
    for (TestFileFunc fileTest: all) {
        cout << endl << "[File " << i++ << " tests]" << endl;
        (*fileTest)();
    }
    return 0;
}
