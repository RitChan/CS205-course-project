/**
 * @file operatorTest.cpp
 * @ingroup test
 * @brief operator tests on Matrix.
 */

#include "gtest.h"
#include "matrix.h"
#include <vector>


class Operator : public ::testing::Test {
protected:
    void SetUp() override {
        matrix = Matrix<int>{
                {1, 2},
                {3, 4}
        };
    }

    Matrix<int> matrix{};
};

/**
 * Test scalar multiplication.
 */
TEST_F(Operator, scalarMultiplicationTest) {
    Matrix<int> matrix1 = 2 * matrix;
    Matrix<int> matrix2 = matrix * 2;
    ASSERT_EQ(matrix1.at(0, 0), 2);
    ASSERT_EQ(matrix1.at(1, 1), 8);
    ASSERT_EQ(matrix2.at(0, 1), 4);
}

/**
 * Test `matrix *= scalar`.
 */
TEST_F(Operator, scalarSelfMultiplicationTest) {
    matrix *= 2;
    ASSERT_TRUE(matrix.at(0, 0) == 2);
    ASSERT_TRUE(matrix.at(1, 1) == 8);
}

/**
 * Test `matrix + matrix`.
 */
TEST_F(Operator, plusOperatorTest) {
    Matrix<int> sum = matrix + matrix;
    ASSERT_TRUE(sum.valid());
    ASSERT_TRUE(sum.at(0, 0) == 2);
    ASSERT_TRUE(sum.at(1, 0) == 6);

    Matrix<int> invalid_sum = Matrix<int>(1, 3) + matrix;
    ASSERT_TRUE(!invalid_sum.valid());
}

/**
 * Test `matrix - matrix`.
 */
TEST_F(Operator, minusOperatorTest) {
    Matrix<int> diff = matrix - matrix;
    ASSERT_TRUE(diff.valid());
    ASSERT_TRUE(diff.at(0, 0) == 0);

    Matrix<int> matrix1(matrix.get_d1size(), matrix.get_d2size());
    diff = matrix1 - matrix;
    ASSERT_TRUE(diff.at(0, 0) == -matrix.at(0, 0));

    matrix1 = Matrix<int>(1, 20);
    diff = matrix - matrix1;
    ASSERT_TRUE(!diff.valid());
}

/**
 * Test `matrix / scalar`.
 */
TEST_F(Operator, divisionOperatorTest) {
    Matrix<int> res = matrix / 2;
    ASSERT_TRUE(res.at(0, 0) == 0);
    ASSERT_TRUE(res.at(1, 1) == 2);
}

/**
 * Test `Matrix::transpose`.
 */
TEST_F(Operator, transposeTest) {
    Matrix<double> matrix1(4, 5);
    matrix1 = matrix1.transpose();
    ASSERT_TRUE(matrix1.valid());
    ASSERT_TRUE(matrix1.get_d2size() == 4);
    ASSERT_TRUE(matrix1.get_d1size() == 5);

    matrix = matrix.transpose();
    ASSERT_TRUE(matrix.at(0, 0) == 1);
    ASSERT_TRUE(matrix.at(1, 0) == 2);
}

/**
 * Test `matrix += matrix`.
 */
TEST_F(Operator, selfPlusTest) {
    Matrix<int> m(1, 10);
    ASSERT_TRUE(!(matrix += m).valid());

    matrix += matrix;
    ASSERT_TRUE(matrix.at(0, 0) == 2);
    ASSERT_TRUE(matrix.at(1, 0) == 6);
}

/**
 * Test `matrix * matrix`.
 */
TEST_F(Operator, multiplicationOperatorTest) {
    Matrix<int> other = matrix * matrix;
    ASSERT_TRUE(other.valid());
    ASSERT_TRUE(other.at(0, 0) == 7);
    ASSERT_TRUE(other.at(1, 1) == 22);

    other = matrix * Matrix<int>(1, 10);
    ASSERT_TRUE(!other.valid());

    other = matrix * Matrix<int>(2, 10);
    ASSERT_TRUE(other.valid());
    ASSERT_TRUE(other.get_d1size() == 2);
    ASSERT_TRUE(other.get_d2size() == 10);
}

/**
 * Test `matrix -= matrix`.
 */
TEST_F(Operator, selfMinusTest) {
    Matrix<int> other = Matrix<int>(2, 2);

    other.at(0, 1) = 5;
    other.at(1, 0) = 2;

    ASSERT_TRUE((matrix -= other).valid());
    ASSERT_TRUE(matrix.at(0, 1) == -3);
    ASSERT_TRUE(matrix.at(1, 0) == 1);

    ASSERT_TRUE(!(matrix -= Matrix<int>(1, 10)).valid());
}

/**
 * Test matrix::hadamard
 */
TEST_F(Operator, hadamardProduct) {
    Matrix<int> other1{
            {2, 2},
            {2, 2}
    };
    Matrix<int> other2{
            {1, 2, 3},
            {2, 3, 4}
    };
    auto result1 = matrix.hadamard(other1);
    auto result2 = matrix.hadamard(other2);

    ASSERT_TRUE(result1.valid());
    EXPECT_EQ(result1.at(0, 0), 2);
    EXPECT_EQ(result1.at(1, 1), 8);
    ASSERT_TRUE(!result2.valid());
}

TEST_F(Operator, multiplyVector) {
    std::vector<int> vec1 = {2, 3};
    std::vector<int> vec2 = {1, 2, 3};

    ASSERT_NO_FATAL_FAILURE(matrix * vec1);
    EXPECT_ANY_THROW(matrix * vec2);

    auto res = matrix * vec1;

    ASSERT_EQ(res.at(0), 8);
    ASSERT_EQ(res.at(1), 18);
}

TEST_F(Operator, crossProduct) {
    // TODO in progress...
}

TEST_F(Operator, reshape) {
    ASSERT_FALSE(matrix.reshape(1, 100));
    ASSERT_TRUE(matrix.reshape(1, 4));
    ASSERT_EQ(matrix.get_d1size(), 1);
    ASSERT_EQ(matrix.get_d2size(), 4);
    ASSERT_EQ(matrix.at(0, 0), 1);
    ASSERT_EQ(matrix.at(0, 1), 2);
    ASSERT_EQ(matrix.at(0, 2), 3);
    ASSERT_EQ(matrix.at(0, 3), 4);
}

TEST_F(Operator, swapRows) {
    matrix.swap_rows(0, 1);
    ASSERT_EQ(matrix.at(0, 0), 3);
    ASSERT_EQ(matrix.at(1, 1), 2);
    ASSERT_ANY_THROW(matrix.swap_rows(100, 1));
}

TEST_F(Operator, equality) {
    Matrix<int> equal_matrix{
            {1, 2},
            {3, 4}
    };

    Matrix<int> diff_matrix1{
            {1, 1},
            {2, 4}
    };

    Matrix<int> diff_matrix2{
            {1, 2, 3},
            {2, 4, 5}
    };

    ASSERT_TRUE(matrix == equal_matrix);
    ASSERT_FALSE(matrix == diff_matrix1);
    ASSERT_FALSE(matrix == diff_matrix2);
}

TEST_F(Operator, gaussianEliminate) {
    Matrix<double> d_matrix{
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };

    Matrix<double> expected1{
            {1, 2, 3},
            {0, -3, -6},
            {0, 0, 0}
    };

    Matrix<double> expected2{
            {1, 2, 3},
            {0, 1, 2},
            {0, 0, 0}
    };

    auto res1 = d_matrix.gaussian_eliminated();
    ASSERT_TRUE(res1.valid());
    ASSERT_EQ(res1.get_d1size(), 3);
    ASSERT_EQ(res1.get_d2size(), 3);
    EXPECT_EQ(res1, expected1);

    auto res2 = d_matrix.gaussian_eliminated(true);
    ASSERT_TRUE(res2.valid());
    ASSERT_EQ(res2.get_d1size(), 3);
    ASSERT_EQ(res2.get_d2size(), 3);
    EXPECT_EQ(res2, expected2);
}

TEST_F(Operator, selfDivideConstant) {
    matrix /= 2;
    EXPECT_EQ(matrix.at(0, 0), 0);
    EXPECT_EQ(matrix.at(0, 1), 1);
    EXPECT_EQ(matrix.at(1, 0), 1);
    EXPECT_EQ(matrix.at(1, 1), 2);
}

TEST_F(Operator, plusConstant) {
    auto res = matrix + 5;
    ASSERT_TRUE(res.valid());
    ASSERT_EQ(res.get_d1size(), 2);
    ASSERT_EQ(res.get_d2size(), 2);
    EXPECT_EQ(res.at(0, 0), 6);
    EXPECT_EQ(res.at(1, 1), 9);
}