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
#include <cppcore/Container/TArray.h>
#include <cppcore/CPPCoreCommon.h>

#include "gtest/gtest.h"

#include <sstream>
#include <iostream>

using namespace cppcore;

// Some test-data
static const size_t ArraySize = 4;
static const float ArrayData[ ArraySize ] = {
    0.0f,
    1.0f,
    2.0f,
    3.0f
};

//-------------------------------------------------------------------------------------------------
///	@class		TArrayTest
///	@ingroup	UnitTest
///
///	@brief	The array tests, includes showcases how to add remove and access data.
//-------------------------------------------------------------------------------------------------
class TArrayTest : public testing::Test {
protected:
    void createArray( const float *pOrig, size_t numItems, TArray<float> &arrayInstance ) {
        for ( size_t i=0; i<numItems; ++i ) {
	    arrayInstance.add( pOrig[ i ] );
	}
    }
};

// Just check whether the array is empty at the beginning
TEST_F( TArrayTest, constructTest ) {
    TArray<float> arrayInstance;
    EXPECT_EQ( true, arrayInstance.isEmpty() );
    EXPECT_EQ( 0U, arrayInstance.size() );
    EXPECT_EQ( arrayInstance.begin(), arrayInstance.end() );
}

// Just checks how to initialize the array
TEST_F( TArrayTest, constructWithSizeTest) {
    TArray<float> arrayInstance( 4 );
    arrayInstance[0] = 0.0f;
    arrayInstance[1] = 1.0f;
    arrayInstance[2] = 2.0f;
    arrayInstance[3] = 3.0f;
    EXPECT_EQ( 4u, arrayInstance.size() );
    for ( size_t i=0; i<4; ++i ) {
        const float f = arrayInstance[i];
	EXPECT_EQ( (float) i, f );
    }
}

TEST_F( TArrayTest, addTest) {
    TArray<float> arrayInstance;
    arrayInstance.add( 0.0f );
    arrayInstance.add( 1.0f );

    EXPECT_EQ( 2u, arrayInstance.size() );
    EXPECT_EQ( 0.0f, arrayInstance[ 0 ] );
    EXPECT_EQ( 1.0f, arrayInstance[ 1 ] );
}

TEST_F( TArrayTest, addItemsTest ) {
    TArray<float> arrayInstance;
    arrayInstance.add( 0.0f );

    float data[2] = { 0, 1 };
    arrayInstance.add( data, 2 );
    EXPECT_EQ( 3u, arrayInstance.size() );
    EXPECT_EQ( 0.0f, arrayInstance[ 0 ] );
    EXPECT_EQ( 0.0f, arrayInstance[ 1 ] );
    EXPECT_EQ( 1.0f, arrayInstance[ 2 ] );

    arrayInstance.add( nullptr, 0 );
    EXPECT_EQ( 3u, arrayInstance.size() );
}

TEST_F( TArrayTest, accessTest) {
    TArray<float> arrayInstance;
    arrayInstance.add( 0.0f );
    arrayInstance.add( 1.0f );
		
    EXPECT_EQ( 0.0f, arrayInstance[ 0 ] );
    EXPECT_EQ( 1.0f, arrayInstance[ 1 ] );
}

TEST_F( TArrayTest, backTest ) {
    float item( 0.0f );
    TArray<float> arrayInstance;
    arrayInstance.add( 1.0f );
    item = arrayInstance.back();
    EXPECT_FLOAT_EQ( 1.0f, item );

    arrayInstance.add( 2.0f );
    item = arrayInstance.back();
    EXPECT_FLOAT_EQ( 2.0f, item );
}

struct foo {
    float m_item;
    foo() : m_item( 1.0f ) {}
};

TEST_F( TArrayTest, constBackTest ) {
    TArray<foo> fooArrayInstance;
    foo foo1;
    foo1.m_item = 1.0f;
    fooArrayInstance.add( foo1 );
    const foo &res1 = fooArrayInstance.back();
    EXPECT_FLOAT_EQ( 1.0f, res1.m_item );

    foo foo2;
    foo2.m_item = 2.0f;
    fooArrayInstance.add( foo2 );
    const foo &res2 = fooArrayInstance.back();
    EXPECT_FLOAT_EQ( 2.0f, res2.m_item );
}

TEST_F( TArrayTest, removeTest) {
    TArray<float> arrayInstance;
    createArray( ArrayData, ArraySize, arrayInstance );

    std::stringstream stream;
    static const size_t Size = 3;
    arrayInstance.remove( 1 );
    EXPECT_EQ( Size, arrayInstance.size() );
    float expectedResult[ Size ] = { 0.0f, 2.0f, 3.0f };
    bool equal = true;
    for ( size_t i=0; i<Size; ++i ) {
        if ( arrayInstance[ i ] != expectedResult[ i ] ) {
            stream << "error in index " << i << std::endl;
            equal = false;
            break;
        }
    }
    EXPECT_TRUE( equal ) << stream.str();
}

TEST_F( TArrayTest, removeItTest) {
    TArray<float> arrayInstance;
    arrayInstance.add( 1.0f );
    EXPECT_EQ( 1u, arrayInstance.size() );
    TArray<float>::Iterator it = arrayInstance.find( 1.0f );
    EXPECT_NE( arrayInstance.end(), it );

    arrayInstance.remove( it );
    EXPECT_EQ( 0u, arrayInstance.size() );
}

TEST_F( TArrayTest, removeBackTest) {
    TArray<float> arrayInstance;
    createArray( ArrayData, ArraySize, arrayInstance );

    arrayInstance.removeBack();
    EXPECT_EQ( 3u, arrayInstance.size() );
    EXPECT_EQ( 2.0f, arrayInstance[ 2 ] );
}

TEST_F( TArrayTest, resizeTest ) {
    TArray<float> arrayInstance;
    EXPECT_EQ( 0u, arrayInstance.size() );

    arrayInstance.resize( 5 );
    EXPECT_EQ( 5u, arrayInstance.size() );
}

TEST_F( TArrayTest, moveTest ) {
    TArray<float> arrayInstance;
    arrayInstance.add( 1.0f );
    arrayInstance.add( 2.0f );
    arrayInstance.add( 3.0f );
    arrayInstance.move( 1, 2 );
}

TEST_F( TArrayTest, reserveTest ) {
    TArray<float> arrayInstance;
    EXPECT_EQ( 0u, arrayInstance.capacity() );

    arrayInstance.reserve( 5 );
    EXPECT_EQ( 5u, arrayInstance.capacity() );

    static const size_t NewSize = 2000;
    arrayInstance.reserve(NewSize);
    EXPECT_EQ( NewSize, arrayInstance.capacity() );
}

TEST_F( TArrayTest, resize_with_init_Test ) {
    TArray<float> arrayInstance;
    EXPECT_EQ( 0u, arrayInstance.capacity() );

    arrayInstance.resize( 10, 1.0f );
    EXPECT_EQ( 10u, arrayInstance.size() );
    for ( size_t i = 0; i < 10; ++i ) {
        EXPECT_FLOAT_EQ( 1.0f, arrayInstance[ i ] );
    }
}

TEST_F( TArrayTest, iterateTest ) {
    TArray<float> arrayInstance;
    createArray( ArrayData, ArraySize, arrayInstance );

    size_t i( 0 );
    for( TArray<float>::Iterator it = arrayInstance.begin( ); it != arrayInstance.end( ); ++it ) {
        ++i;
    }
    EXPECT_EQ( i, arrayInstance.size() );
}

TEST_F( TArrayTest, preIncIterateTest ) {
    TArray<float> arrayInstance;
    createArray( ArrayData, ArraySize, arrayInstance );

    bool ok = true;
    try {
 	size_t i( 0 );
        for( TArray<float>::Iterator it = arrayInstance.begin( ); it != arrayInstance.end( ); ++it ) {
            float tmp = *it;
			EXPECT_EQ( tmp, ArrayData[ i ] );
			++i;
		}
	} catch (...)	{
		ok = false;	
	}
	EXPECT_TRUE( ok );
}

TEST_F( TArrayTest, postIncIterateTest ) {
	TArray<float> arrayInstance;
	createArray( ArrayData, ArraySize, arrayInstance );

	bool ok = true;
	try {
		size_t i(0);
        for( TArray<float>::Iterator it = arrayInstance.begin( ); it != arrayInstance.end( ); it++ ) {
            float tmp = *it;
			EXPECT_EQ( tmp, ArrayData[ i ] );
			++i;
		}
	} catch (...) {
		ok = false;	
	}
	EXPECT_TRUE( ok );
}

TEST_F( TArrayTest, findTest )	{
    TArray<float> arrayInstance;
	arrayInstance.add( 0.0f );
	arrayInstance.add( 1.0f );
	arrayInstance.add( 2.0f );
	arrayInstance.add( 3.0f );
	EXPECT_EQ( 4u, arrayInstance.size() );

    TArray<float>::Iterator it = arrayInstance.find( 1.0f );
	EXPECT_NE( it, arrayInstance.end() );
	EXPECT_EQ( *it, 1.0f );
}

TEST_F( TArrayTest, ContainerClearTest ) {
    TArray<float*> arrayInstance;
    ContainerClear( arrayInstance );
    EXPECT_TRUE( arrayInstance.isEmpty() );

    arrayInstance.add( new float( 0.0f ) );
    arrayInstance.add( new float( 1.0f ) );
    arrayInstance.add( new float( 2.0f ) );

    EXPECT_EQ( arrayInstance.size(), 3U );
    ContainerClear( arrayInstance );
    EXPECT_EQ( arrayInstance.size(), 0U );
    EXPECT_TRUE( arrayInstance.isEmpty() );
}

//---------------------------------------------------------------------------------------------
//	Crash when iterating an empty array.
//---------------------------------------------------------------------------------------------
TEST_F( TArrayTest, bug_IterateEmptyListTest )	{
    TArray<float> arrayInstance;
	bool ok = true;
	try {
        for( TArray<float>::Iterator it = arrayInstance.begin( ); it != arrayInstance.end( ); ++it );
	} catch ( ... ) {
		ok = false;
	}
	EXPECT_TRUE( ok );
}

//---------------------------------------------------------------------------------------------
//	Heap corruption after grow.
//---------------------------------------------------------------------------------------------
TEST_F( TArrayTest, bug_AddHeapCorruptTest ) {
    TArray<float> arrayInstance;
    for ( size_t i=0; i<50; ++i ) {
        arrayInstance.add( ( float ) i );
    }
}
