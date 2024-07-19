/*-------------------------------------------------------------------------------------------------
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
-------------------------------------------------------------------------------------------------*/
#include <cppcore/Memory/TPoolAllocator.h>

#include <gtest/gtest.h>

using namespace cppcore;

class TPoolAllocatorTest : public testing::Test {
protected:
    // empty
};

struct PoolItem {
    int id;

    PoolItem()
    : id(0) {
        // empty
    }
};

TEST_F(TPoolAllocatorTest, createTest) {
    bool ok( true );
    try {
        TPoolAllocator<PoolItem> allocator;
    } catch (...) {
        ok = false;
    }
    EXPECT_TRUE( ok );
}

static const size_t NumItems = 500;

TEST_F(TPoolAllocatorTest, alloc_access_Test) {
    TPoolAllocator<PoolItem> allocator;
    allocator.reserve(NumItems);
    for (size_t i = 0; i < NumItems; ++i) {
        PoolItem *item = allocator.alloc();
        EXPECT_NE(nullptr, item);
    }

    PoolItem *nullItem = allocator.alloc();
    EXPECT_NE(nullptr, nullItem);
}

TEST_F(TPoolAllocatorTest, countAllocsTest) {
    TPoolAllocator<PoolItem> allocator;
    allocator.reserve(NumItems);

    static_cast<void>(allocator.alloc());
    EXPECT_EQ(499u, allocator.freeMem());
}

TEST_F(TPoolAllocatorTest, getAllocsTest) {
    TPoolAllocator<PoolItem> allocator;
    allocator.reserve(NumItems);

    std::string allocs;
    allocator.dumpAllocations(allocs);
    int res = strncmp("Number allocations = 0\n", allocs.c_str(), allocs.size());
    EXPECT_EQ( 0, res);
}

TEST_F(TPoolAllocatorTest, clearTest ) {
    TPoolAllocator<int> allocator;
    allocator.reserve( 100u );
    allocator.clear();
    EXPECT_EQ( allocator.freeMem(), 0u );
}

TEST_F(TPoolAllocatorTest, resizeTest) {
    TPoolAllocator<int> allocator;
    allocator.resize(100);

    for (size_t i = 0; i < 200; ++i) {
        EXPECT_NE(nullptr, allocator.alloc());
    }
    EXPECT_EQ(200u, allocator.capacity());
}

TEST_F(TPoolAllocatorTest, releaseTest) {
    TPoolAllocator<int> allocator;
    allocator.resize(100);
    for (size_t i = 0; i < 200; ++i) {
        EXPECT_NE(nullptr, allocator.alloc());
    }

    allocator.release();
    for (size_t i = 0; i < 200; ++i) {
        EXPECT_NE(nullptr, allocator.alloc());
    }

    EXPECT_EQ(200u, allocator.capacity());
}
