#ifndef TESTING_TEST_H
#define TESTING_TEST_H

#include "gtest/gtest.h"

TEST(AddTest,IsEqual){
ASSERT_EQ(1,1);
ASSERT_EQ(17,17);
}

TEST(EqualTest,IsTrue){
ASSERT_TRUE(true);
ASSERT_FALSE(false);
}

#endif
