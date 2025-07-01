/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2025 Kim Kulling

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
-----------------------------------------------------------------------------------------------*/
#include <gtest/gtest.h>

#include <cstdint>
#include <cppcore/Common/TStringView.h>
#include <cppcore/Container/TAlgorithm.h>

using namespace cppcore;

class TStringViewTest : public ::testing::Test {};

using StringView = TStringView<char>;

TEST_F(TStringViewTest, createTest) {

    StringView sv("this is a test", 14L);
    auto start = sv.begin();
    auto end = sv.end();

    size_t d = distance(start, end);
    EXPECT_EQ(d, 14);
}

TEST_F(TStringViewTest, dataTest) {
    StringView sv("this is a test", 14L);
    const char *ptr = sv.data(4);
    EXPECT_NE(ptr, nullptr);

    auto end = sv.end();

    size_t d = distance(ptr, end);
    EXPECT_EQ(d, 10);

    const char *invalidPtr = sv.data(16);
    EXPECT_EQ(invalidPtr, nullptr);
}

TEST_F(TStringViewTest, iterateTest) {
    constexpr char tag[] = "this is a test";
    StringView sv(tag, 14L);
    size_t i{0};
    for (auto it = sv.begin(); it != sv.end(); ++it) {
        EXPECT_EQ(tag[i++], *it);
    }
}
