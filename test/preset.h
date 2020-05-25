/**
 * @file preset.h
 * @ingroup test
 * @brief Presets included in test files
 */

#ifndef COURSEPROJECT_PRESET_H
#define COURSEPROJECT_PRESET_H

#include <iostream>
#include "test_assert.h"

using namespace std;

/**
 * Type for every test function
 * @return return test status, 0 for success and other values for failure
 */
typedef int (*TestFunc)();

/**
 * Enum for test status
 */
enum {
    PASS = 0, FAILURE = -1
};
#endif //COURSEPROJECT_PRESET_H
