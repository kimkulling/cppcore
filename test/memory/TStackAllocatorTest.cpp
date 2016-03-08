/*
-------------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2016 Kim Kulling

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

#include <cppcore/Memory/TStackAllocator.h>

#include "gtest/gtest.h"

using namespace CPPCore;

//---------------------------------------------------------------------------------------------
class TStackAllocatorTest : public testing::Test {
protected:
};

TEST_F( TStackAllocatorTest, CreateTest ) {
    bool ok( true );
    try {
        TStackAllocator<int> myAllocator( 1024 );
    }
    catch ( ... ) {
        ok = false;
    }
    EXPECT_TRUE( ok );
}

TEST_F( TStackAllocatorTest, AllocReleaseTest ) {
    TStackAllocator<int> myAllocator( 1024 );

    int *init( myAllocator.alloc( 1 ) );
    const size_t size0( myAllocator.freeMem() );
    EXPECT_TRUE( nullptr != init );

    const size_t size1( myAllocator.freeMem() );
    int *myArray = myAllocator.alloc( 10 );
    EXPECT_TRUE( nullptr != myArray );

    myAllocator.release( myArray );
    const size_t size2( myAllocator.freeMem() );
}
