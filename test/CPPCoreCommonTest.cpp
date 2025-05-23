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
#include <cppcore/CPPCoreCommon.h>
#include <cppcore/Container/TArray.h>

#include "gtest/gtest.h"

using namespace cppcore;

//---------------------------------------------------------------------------------------------
class CPPCoreCommonTest : public testing::Test {
protected:
};

class NoCopyMock {
    CPPCORE_NONE_COPYING( NoCopyMock )

public:
    NoCopyMock() {
        // empty
    }
};

TEST_F( CPPCoreCommonTest, NoneCopyingTest ) {
    bool success( true );
    try {
        NoCopyMock mymock;
    } catch( ... ) {
        success = false;
    }
    EXPECT_TRUE( success );
}

static void createTestArray( TArray<int*> &myArray ) {
    for ( size_t i = 0; i < 10; i++ ) {
        myArray.add( new int );
    }
}

TEST_F( CPPCoreCommonTest, ContainerClearTest ) {
    TArray<int*> myArray;
    createTestArray( myArray );
    ContainerClear( myArray );
    EXPECT_TRUE( myArray.isEmpty() );
}

void deleterTestFunc( TArray<int*> &myArray ) {
    if ( myArray.isEmpty() ) {
        return;
    }
    for ( size_t i = 0; i < myArray.size(); i++ ) {
        delete myArray[ i ];
    }
    myArray.resize( 0 );
}

TEST_F( CPPCoreCommonTest, ContainerClearWithDeleterTest ) {
    TArray<int*> myArray;
    createTestArray( myArray );
    ContainerClear( myArray, deleterTestFunc );
    EXPECT_TRUE( myArray.isEmpty() );
}

TEST_F( CPPCoreCommonTest, ArraySizeTest ) {
    int array[ 10 ];
    size_t size = CPPCORE_ARRAY_SIZE( array );
    EXPECT_EQ( size, 10U );
}
