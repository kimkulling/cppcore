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
#include <cppcore/Common/TBitField.h>
#include <cstdint>

#include "gtest/gtest.h"

using namespace cppcore;

class TBitFieldTest : public testing::Test {
    // empty
};

TEST_F(TBitFieldTest, CreateTest) {
    bool ok = true;
    try {
        TBitField<uint32_t> bitfield;
        TBitField<uint32_t> bitfield1(0);    
    } catch (...) {
        ok = false;
    }
    EXPECT_TRUE(ok);
}

TEST_F(TBitFieldTest, GetSetTest) {
    TBitField<uint32_t> bitfield(0);
    EXPECT_FALSE(bitfield.getBit(1));
    bitfield.setBit(1);
    EXPECT_TRUE(bitfield.getBit(1));

    bitfield.setBit(1);
    bitfield.clearBit(1);
    EXPECT_FALSE(bitfield.getBit(1));

    for (int i = 0; i < 10; ++i) {
        bitfield.setBit(i, true);
    }
    bitfield.clear();
    for (int i = 0; i < 10; ++i) {
        EXPECT_FALSE(bitfield.getBit(i));
    }
}

TEST_F(TBitFieldTest, maxBitsTest) {
    TBitField<uint32_t> bitfield1(0);
    size_t numBits = 0;
    numBits = bitfield1.maxBits();
    EXPECT_EQ(32u, numBits);
    TBitField<uint64_t> bitfield2(0);
    numBits = bitfield2.maxBits();
    EXPECT_EQ(64u, numBits);
    TBitField<uint8_t> bitfield3(0);
    numBits = bitfield3.maxBits();
    EXPECT_EQ(8u, numBits);
}