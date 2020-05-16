//
// Created by chenh on 5/11/2020.
//
#include "test_header.h"
#include <iostream>
using namespace std;

int main() {
    int i = 0;
    for (TestFileFunc fileTest: all) {
        cout << endl << "[File " << i++ << " tests]" << endl;
        (*fileTest)();
    }
}
