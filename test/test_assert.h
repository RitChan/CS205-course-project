/**
 * @file test_assert.h
 * @ingroup test
 * @brief Provides assertion macros for tests.
 */

#ifndef COURSEPROJECT_TEST_ASSERT_H
#define COURSEPROJECT_TEST_ASSERT_H
#include <iostream>

/**
 * Test whether an expression is true or not.
 *
 * If true, do nothing; * If false, return -1.
 */
#define assertTrue(expr)\
if(!(expr)) {\
    std::cout << "assertTrue: failed: '" << #expr << "' should be true" << endl;\
    return -1;\
}

/**
 * Test whether an expression throws exception or not.
 *
 * If it throws exception, do nothing; if no exception is thrown, return -1;
 */
#define expectException(expr)\
try {\
    expr;\
    std::cout << "expectException: failed: '" << #expr << "' should throw exception" << endl;\
    return -1;\
} catch(...) {}

/**
 * Test whether an expression executes without throwing exception or not.
 *
 * If it throws exception, return -1; if no exception is thrown, do noting;
 */
#define assertNoException(expr)\
try {\
    expr;\
} catch(...) {\
    std::cout << "assertNoException: failed: " << #expr << "' should NOT throw exception" << endl;\
    return -1;\
}
#endif //COURSEPROJECT_TEST_ASSERT_H
