/*-----------------------------------------------------------------------------------------------
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
-----------------------------------------------------------------------------------------------*/
#include <gtest/gtest.h>
#include <cppcore/Common/TOptional.h>

using namespace ::cppcore;

class TOptionalTest : public ::testing::Test {};

TEST_F(TOptionalTest, createInstance_success) {
    constexpr int ValInt = 1;
    TOptional<int> test_int(ValInt);

    EXPECT_FALSE(test_int.isInited());
    test_int.set(1);
    EXPECT_TRUE(test_int.isInited());
    EXPECT_EQ(test_int.value(), ValInt);

    constexpr float ValFloat = 1.0f;
    TOptional<float> test_float(ValFloat);

    EXPECT_FALSE(test_float.isInited());
    test_float.set(1);
    EXPECT_TRUE(test_float.isInited());
    EXPECT_EQ(test_float.value(), ValFloat);
}
