#include <cppcore/Container/TAlgorithm.h>
#include <cppcore/Container/TArray.h>
#include <cppcore/CPPCoreCommon.h>

#include "gtest/gtest.h"

#include <iostream>

using namespace cppcore;

class TAlgorithmTest : public testing::Test {};

TEST_F(TAlgorithmTest, distanceTest) {
    TArray<float> theArray;
    theArray.add(1.0f);
    theArray.add(3.0f);
    theArray.add(2.0f);

    size_t dist = distance(theArray.begin(), theArray.end());
    EXPECT_EQ(dist, 3u);

    dist = distance(theArray.begin()+1, theArray.end());
    EXPECT_EQ(dist, 2u);
}
