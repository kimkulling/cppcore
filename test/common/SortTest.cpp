/*
-------------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2024 Kim Kulling

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-------------------------------------------------------------------------------------------------
*/
#include <cppcore/Common/Sort.h>

#include "gtest/gtest.h"

using namespace cppcore;

class SortTest : public testing::Test {
public:
    
protected:
    // empty
};

TEST_F(SortTest, isSortedTest ) {
    int32_t arr[] = {1,2,3,4,5};
    bool sorted = isSorted(arr, 5, sizeof(int32_t), compAscending<int32_t>);
    EXPECT_TRUE(sorted);
}

TEST_F(SortTest, isNotSortedTest) {
    int32_t arr[] = { 1, 2, 3, 5, 4 };
    bool sorted = isSorted(arr, 5, sizeof(int32_t), compAscending<int32_t>);
    EXPECT_FALSE(sorted);
}

TEST_F(SortTest, quicksortTest) {
    int32_t arr[] = { 1, 2, 3, 5, 4 };
    quicksort(&arr[0], &arr[0], 5, sizeof(int32_t), compAscending<int32_t>);
    bool sorted = isSorted(arr, 5, sizeof(int32_t), compAscending<int32_t>);
    EXPECT_TRUE(sorted);
}
