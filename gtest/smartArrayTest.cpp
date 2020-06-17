//
// Created by chenh on 6/16/2020.
//
#include "smart_array.h"
#include "gtest.h"

using namespace mat;

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
    EXPECT_EQ(ary.get_ref_count(), 1);
    for (int i = 0; i < 9; i++)
        EXPECT_EQ(ary[i], 0);
}

TEST_F(SmartArrayTest, referToTest) {
    auto ref = ary.shallow_copy();
    ASSERT_EQ(ref.get_ref_count(), 2);
}

TEST_F(SmartArrayTest, releaseTest) {
    auto ref = ary.shallow_copy();
    ref.release();
    EXPECT_EQ(ary.get_ref_count(), 1);
    ary.release();
}
