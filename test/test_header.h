//
// Created by chenh on 5/11/2020.
//

#ifndef COURSEPROJECT_TEST_HEADER_H
#define COURSEPROJECT_TEST_HEADER_H
typedef void (*TestFileFunc)();

void test_file_0_main();

TestFileFunc all[] = {
        test_file_0_main
};
#endif //COURSEPROJECT_TEST_HEADER_H
