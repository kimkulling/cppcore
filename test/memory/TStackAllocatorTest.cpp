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
#include <cppcore/Memory/TStackAllocator.h>

#include <gtest/gtest.h>

using namespace cppcore;

class TStackAllocatorTest : public testing::Test {
protected:
};

TEST_F( TStackAllocatorTest, CreateTest ) {
    bool ok( true );
    try {
        TStackAllocator<int> myAllocator( 1024 );
    } catch ( ... ) {
        ok = false;
    }
    EXPECT_TRUE( ok );
}

TEST_F( TStackAllocatorTest, AllocReleaseTest ) {
    TStackAllocator<int> myAllocator( 1024 );
    EXPECT_EQ( 1024*sizeof(int), myAllocator.freeMem() );

    int *init( myAllocator.alloc( 1 ) );
    const size_t size0( myAllocator.freeMem() );
    EXPECT_TRUE( nullptr != init );

    int *myArray = myAllocator.alloc( 10 );
    const size_t size1( myAllocator.freeMem() );
    EXPECT_TRUE( nullptr != myArray );
    EXPECT_TRUE( size1 < size0 );

    bool ok( true );
    myAllocator.release( myArray );
    const size_t size2( myAllocator.freeMem() );
    EXPECT_EQ( size2, size0 );
    EXPECT_TRUE( ok );
}

TEST_F( TStackAllocatorTest, badAllocTest ) {
    TStackAllocator<int> myAllocator( 1024 );
    EXPECT_EQ( 1024 * sizeof( int ), myAllocator.freeMem() );

    int *ptr( myAllocator.alloc( 2048 ) );
    EXPECT_TRUE( nullptr == ptr );
}

TEST_F( TStackAllocatorTest, badReleaseTest ) {
    TStackAllocator<int> myAllocator( 1024 );
    EXPECT_EQ( 1024 * sizeof( int ), myAllocator.freeMem() );

    bool ok( true );
    ok = myAllocator.release( nullptr );
    EXPECT_FALSE( ok );
}

TEST_F( TStackAllocatorTest, dumpAllocationsTest ) {
    TStackAllocator<int> myAllocator( 1024 );
    static_cast< void >( myAllocator.alloc( 100 ) );

    std::string dumps, exp = "Number allocations = 1\n";
    myAllocator.dumpAllocations( dumps );
    EXPECT_EQ( exp, dumps );
}
