/*
-------------------------------------------------------------------------------------------------
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
-------------------------------------------------------------------------------------------------
*/
#include <gtest/gtest.h>

#include <cppcore/Common/TStringBase.h>

using namespace cppcore;

class TStringBaseTest : public ::testing::Test {};

TEST_F(TStringBaseTest, createTest) {
    TStringBase<char> string_1;
    string_1.set("test", 4);
    
    TStringBase<char> string_2("test", 4);
    EXPECT_EQ(string_1, string_2);

    TStringBase<char> string_3("test", 4);
    EXPECT_EQ(string_3, string_2);
}

TEST_F(TStringBaseTest, setResetTest) {
    TStringBase<char> string_1;
    EXPECT_EQ(string_1.size(), 0);
    EXPECT_EQ(string_1.capacity(), 512);
    string_1.set("test", 4);
    EXPECT_EQ(string_1.size(), 4);
    EXPECT_EQ(0, strncmp(string_1.c_str(), "test", 4));
    string_1.reset();
    EXPECT_EQ(string_1.size(), 0);
}

TEST_F(TStringBaseTest, setClearTest) {
    TStringBase<char> string_1("test", 4);
    EXPECT_EQ(string_1.capacity(), 512);
    EXPECT_EQ(string_1.size(), 4);
    EXPECT_FALSE(string_1.isEmpty());

    string_1.clear();
    EXPECT_EQ(string_1.size(), 0);
    EXPECT_TRUE(string_1.isEmpty());
}
