/**
 * @file statisticTest.cpp
 * @ingroup test
 * @brief Statistic operation tests on Matrix.
 */
#include "gtest.h"
#include "matrix.h"


class Statistic : public ::testing::Test {
protected:
    void SetUp() override {
        matrix = Matrix<int>{
                {1, 2, 3},
                {4, 5, 6}
        };
    }

    Matrix<int> matrix{};
};

/**
 * Test sum.
 */
TEST_F(Statistic, sum) {
    // test sum
    ASSERT_TRUE(matrix.sum() == 21);
}

/**
 * Test max.
 */
TEST_F(Statistic, max) {
    // test max
    ASSERT_TRUE(matrix.max() == 6);
}

/**
 * Test min.
 */
TEST_F(Statistic, min) {
    // test min
    ASSERT_TRUE(matrix.min() == 1);
}

/**
 * Test row_max.
 */
TEST_F(Statistic, rowMax) {
    // test row_max
    ASSERT_TRUE(matrix.row_max(0) == 3);
    ASSERT_TRUE(matrix.row_max(1) == 6);
}

/**
 * Test row_min.
 */
TEST_F(Statistic, rowMin) {
    // test row_min
    ASSERT_TRUE(matrix.row_min(0) == 1);
    ASSERT_TRUE(matrix.row_min(1) == 4);
}

/**
 * Test row_sum.
 */
TEST_F(Statistic, rowSum) {
    // test row_sum
    ASSERT_TRUE(matrix.row_sum(0) == 6);
    ASSERT_TRUE(matrix.row_sum(1) == 15);
}

/**
 * Test col_min.
 */
TEST_F(Statistic, colMin) {
    // test col_min
    ASSERT_TRUE(matrix.col_min(0) == 1);
    ASSERT_TRUE(matrix.col_min(2) == 3);
}

/**
 * Test col_max.
 */
TEST_F(Statistic, colMax) {
    // test col_max
    ASSERT_TRUE(matrix.col_max(0) == 4);
    ASSERT_TRUE(matrix.col_max(1) == 5);
}

/**
 * Test col_sum.
 */
TEST_F(Statistic, colSum) {
    // test col_sum
    ASSERT_TRUE(matrix.col_sum(0) == 5);
    ASSERT_TRUE(matrix.col_sum(2) == 9);
}

TEST_F(Statistic, determinant) {
    Matrix<double> d_matrix1{
            {1, 2},
            {3, 4}
    };

    Matrix<double> d_matrix2{
            {1, 2, 3},
            {4, 5, 6},
            {5, 7, 10}
    };

    Matrix<double> d_matrix3{
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };

    auto det1 = d_matrix1.determinant();
    ASSERT_DOUBLE_EQ(det1, -2);

    auto det2 = d_matrix2.determinant();
    ASSERT_DOUBLE_EQ(det2, -3);

    auto det3 = d_matrix3.determinant();
    ASSERT_DOUBLE_EQ(det3, 0);
}