//
// Created by chenh on 6/16/2020.
//

#include "gtest.h"
#include "matrix.h"
#include "matrix_view.h"

class MatrixViewTest: public ::testing::Test {
protected:
    void SetUp() override {
        matrix = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
        };
    }

    Matrix<int> matrix;
};

TEST_F(MatrixViewTest, ctor1) {
    MatrixView<int> view(matrix, {0, 2}, {0, 2});
    ASSERT_EQ(view.get_d1size(), 2);
    ASSERT_EQ(view.get_d2size(), 2);
    EXPECT_EQ(view.at(0, 1), 3);
    EXPECT_EQ(view.at(1, 0), 7);
}

TEST_F(MatrixViewTest, ctor2) {
    MatrixView<int> view(matrix, 1, 3, 1, 3);
    ASSERT_EQ(view.get_d1size(), 2);
    ASSERT_EQ(view.get_d2size(), 2);
    EXPECT_EQ(view.at(0, 1), 6);
    EXPECT_EQ(view.at(1, 0), 8);
}