//
// Created by chenh on 6/16/2020.
//
#include "smart_array.h"
#include "gtest.h"

class SmartArrayTest: public ::testing::Test {
protected:

    void SetUp() override {
        ary = SmartArray<int>::make_array(10);
    }

    void TearDown() override {
        ary.release();
    }

    SmartArray<int> ary{};
};

TEST_F(SmartArrayTest, makeArrayTest) {
    ASSERT_TRUE(ary.ref_count != nullptr);
    ASSERT_TRUE(ary.elem != nullptr);
    EXPECT_EQ(*ary.ref_count, 1);
    for (int i = 0; i < 9; i++)
        EXPECT_EQ(ary[i], 0);
}

TEST_F(SmartArrayTest, referToTest) {
    auto ref = ary.copy();
    ASSERT_TRUE(ref.ref_count != nullptr);
    ASSERT_TRUE(ref.elem != nullptr);
    ASSERT_EQ(*ref.ref_count, 2);
}

TEST_F(SmartArrayTest, releaseTest) {
    auto ref = ary.copy();
    ref.release();
    EXPECT_EQ(*ary.ref_count, 1);
    ary.release();
    EXPECT_TRUE(ary.ref_count == nullptr);
    EXPECT_TRUE(ary.elem == nullptr);
}