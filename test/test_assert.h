//
// Created by chenh on 5/11/2020.
//

#ifndef COURSEPROJECT_TEST_ASSERT_H
#define COURSEPROJECT_TEST_ASSERT_H
#include <iostream>

#define assertTrue(expr)\
if(!(expr)) {\
    std::cout << "assertTrue: failed:" << #expr << endl;\
    return -1;\
}

#define expectException(expr)\
try {\
    expr;\
    std::cout << "expectException: failed: " << #expr << endl;\
    return -1;\
} catch(...) {}

#define assertNoException(expr)\
try {\
    expr;\
} catch(...) {\
    std::cout << "assertNoException: failed: " << #expr << endl;\
    return -1;\
}
#endif //COURSEPROJECT_TEST_ASSERT_H
