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
#include <cppcore/Memory/TScratchAllocator.h>

#include <gtest/gtest.h>

using namespace cppcore;

class TScratchAllocatorTest : public testing::Test {};

static constexpr size_t BufferSize = 1024u;

TEST_F(TScratchAllocatorTest, CreateTest) {
    bool ok( true );
    try {
        ScratchAllocator myAllocator(BufferSize);
    } catch ( ... ) {
        ok = false;
    }
    EXPECT_TRUE( ok );
}

TEST_F(TScratchAllocatorTest, AllocTest) {
    ScratchAllocator myAllocator(BufferSize);
    char *ptr1 = myAllocator.alloc(512);
    EXPECT_NE(ptr1, nullptr);
    EXPECT_EQ(myAllocator.capacity(), BufferSize);
    EXPECT_EQ(myAllocator.freeMem(), 512);
    EXPECT_EQ(myAllocator.reservedMem(), 512);

    char *ptr2 = myAllocator.alloc(600);
    EXPECT_EQ(ptr2, nullptr);

    myAllocator.clear();
}

TEST_F(TScratchAllocatorTest, ClearTest) {
    ScratchAllocator myAllocator(BufferSize);
    EXPECT_EQ(myAllocator.capacity(), BufferSize);
    EXPECT_EQ(myAllocator.freeMem(), BufferSize);

    myAllocator.clear();
    EXPECT_EQ(myAllocator.capacity(), 0u);
    EXPECT_EQ(myAllocator.freeMem(), 0u);
}
