/**
 * @file basicTest.cpp
 * @ingroup test
 * @brief Basic tests on Matrix.
 */

#include "gtest.h"
#include "matrix.h"


class Basic : public ::testing::Test {
protected:
    Matrix<int> matrix{};
};

TEST_F(Basic, indexingTest0) {
    matrix = Matrix<int>(5, 6);
    ASSERT_TRUE(matrix.get_d1size() == 5);
    ASSERT_TRUE(matrix.get_d2size() == 6);
    ASSERT_ANY_THROW(matrix.at(5));
    ASSERT_ANY_THROW(matrix.at(-1));
    ASSERT_NO_THROW(matrix.at(4));
    ASSERT_NO_THROW(matrix.at(0));

    // triangle check
    matrix = Matrix<int>(10, 1);
    ASSERT_TRUE(matrix.get_d1size() == 10);
    ASSERT_TRUE(matrix.get_d2size() == 1);
    ASSERT_ANY_THROW(matrix.at(10));
    ASSERT_NO_THROW(matrix.at(6));

    ASSERT_ANY_THROW(matrix.at(1).at(1));
    ASSERT_NO_THROW(matrix.at(1).at(0));
}

TEST_F(Basic, indexingTest1) {
    matrix = Matrix<int>(5, 6);
    ASSERT_ANY_THROW(matrix.at(5, 6));
    ASSERT_NO_THROW(matrix.at(4, 5));
    ASSERT_TRUE(matrix.at(4, 5) == 0);
    ASSERT_TRUE((matrix.at(0, 0) = 1) == 1);
}

TEST_F(Basic, listConstructorTest) {
    Matrix<int> matrix1{
            {1, 2, 3},
            {4, 5, 6}
    };
    ASSERT_TRUE(matrix1.valid());
    ASSERT_TRUE(matrix1.get_d1size() == 2);
    ASSERT_TRUE(matrix1.get_d2size() == 3);
    ASSERT_TRUE(matrix1.at(0, 0) == 1);
    ASSERT_TRUE(matrix1.at(1, 2) == 6);

    Matrix<int>matrix2{
            {}
    };
    ASSERT_TRUE(!matrix2.valid());

    Matrix<int>matrix3{
            {1, 2},
            {0}
    };
    ASSERT_TRUE(!matrix3.valid());
}