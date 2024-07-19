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
#include <cppcore/Container/TList.h>

#include "gtest/gtest.h"

#include <sstream>
#include <iostream>
#include <vector>

using namespace cppcore;

//-------------------------------------------------------------------------------------------------
/// @class     TListTest
/// @ingroup   UnitTest
///
/// @brief     The array tests.
//-------------------------------------------------------------------------------------------------
class TListTest : public testing::Test {
protected:
    void createList( size_t numEntries, TList<float> &dataList, std::vector<float> &values ) {
        values.resize( 0 );
        dataList.clear();
        for( size_t i = 0; i<numEntries; ++i ) {
            float value = i*1.0f;
            dataList.addBack( value );
            values.push_back( value );
        }
    }
};

TEST_F( TListTest, constructTest) {
    TList<float> listTest;
    EXPECT_TRUE( listTest.isEmpty() );
    EXPECT_EQ( 0u, listTest.size() );
}

TEST_F( TListTest, addBackTest) {
    TList<float> listTest;
    listTest.addBack( 1.0f );
    listTest.addBack( 2.0f );
    listTest.addBack( 3.0f );

    EXPECT_EQ( 3u, listTest.size() );
    EXPECT_TRUE( !listTest.isEmpty() ); 
}

TEST_F( TListTest, addFrontTest) {
    TList<float> listTest;
    listTest.addFront( 1.0f );
    listTest.addFront( 2.0f );
    listTest.addFront( 3.0f );
		
    EXPECT_EQ( 3u, listTest.size() );
    EXPECT_TRUE( !listTest.isEmpty() ); 
}

TEST_F( TListTest, copyTest ) {
    TList<float> listTest;
    TList<float> copyTest1( listTest );
    EXPECT_TRUE( copyTest1.isEmpty() );
    EXPECT_EQ( 0u, copyTest1.size() );

    listTest.addBack( 1.0f );
    listTest.addBack( 2.0f );
    TList<float> copyTest2( listTest );
    EXPECT_TRUE( !copyTest2.isEmpty() );
    EXPECT_EQ( 2u, copyTest2.size() );
}

TEST_F( TListTest, accessTest ) {
    static constexpr size_t numEntries = 10;
    TList<float> listTest;
    std::vector<float> values;
    createList( numEntries, listTest, values );

    EXPECT_EQ( numEntries, listTest.size() );
    EXPECT_TRUE( !listTest.isEmpty() ); 

    size_t dataIdx = 0;
    for( TList<float>::Iterator it = listTest.begin( ); it != listTest.end( ); ++it ) {
        float listVal = *it;
        float orig = values[ dataIdx ];
        EXPECT_EQ( listVal, orig );
        ++dataIdx;
    }
}

TEST_F( TListTest, clearTest ) {
    static constexpr size_t numEntries = 10;
    TList<float> listTest;
    std::vector<float> values;
    createList( numEntries, listTest, values );

    listTest.clear();
    EXPECT_EQ( listTest.size(), 0u );
    EXPECT_TRUE( listTest.isEmpty() );
}

TEST_F( TListTest, removeTest )	{
    static constexpr size_t numEntries = 10;
    TList<float> listTest;
    std::vector<float> values;

    createList( numEntries, listTest, values );
		
    for ( size_t i=0; i<numEntries; ++i ) {
        const float value = listTest.front( );
        EXPECT_EQ( value, values[ i ] );
        listTest.removeFront();
    }
}

TEST_F( TListTest, isEmptyTest ) {
    TList<float> listTest;
    EXPECT_TRUE( listTest.isEmpty() );
    listTest.addBack( 1.0f );
    listTest.addBack( 2.0f );
    listTest.removeFront();
    listTest.removeFront();
    EXPECT_TRUE( listTest.isEmpty() );
}
	
TEST_F( TListTest, bug_IterateEmptyListTest ) {
    TList<float> listTest;
    bool ok = true;
    try {
        for( TList<float>::Iterator it = listTest.begin( ); it != listTest.end( ); ++it );
    } catch ( ... )	{
        ok = false;
    }
    EXPECT_TRUE( ok );
}
