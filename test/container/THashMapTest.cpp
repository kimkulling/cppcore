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
#include <cppcore/Container/THashMap.h>

#include "gtest/gtest.h"

using namespace ::cppcore;

class THashMapTest : public ::testing::Test {
    // empty
};

TEST_F( THashMapTest, constructTest ) {
    bool ok( true );
    try {
        THashMap<unsigned int, unsigned int> myHashMap;
    } catch( ... ) {
        ok = false;
    }

    // Assert
    EXPECT_TRUE( ok );
}

TEST_F( THashMapTest, clearTest ) {
    THashMap<unsigned int, unsigned int> myHashMap( 1 );
    myHashMap.insert( 1, 10 );
    myHashMap.insert( 2, 10 );
    myHashMap.insert( 3, 10 );

    myHashMap.clear();

    EXPECT_EQ( myHashMap.size(), 0u );
}

TEST_F( THashMapTest, insertTest ) {
    THashMap<unsigned int, unsigned int> myHashMap;
    bool hasKey( true );

    size_t size = 0;
    size = myHashMap.size();
    EXPECT_EQ( size, 0u );

    hasKey = myHashMap.hasKey( 1 );
    EXPECT_FALSE( hasKey );
    
    myHashMap.insert( 1, 10 );
    hasKey = myHashMap.hasKey( 1 );
    EXPECT_TRUE( hasKey );

    size = myHashMap.size();
    EXPECT_EQ( size, 1u );

    bool success = false;
    unsigned int value = 0;
    success = myHashMap.getValue( 1, value );
    EXPECT_TRUE( success );
    EXPECT_EQ( value, 10u );

    myHashMap.insert( 2, 10 );
    hasKey = myHashMap.hasKey( 2 );
    EXPECT_TRUE( hasKey );

    size = myHashMap.size();
    EXPECT_EQ( size, 2u );
}

TEST_F( THashMapTest, collideTest ) {
    THashMap<unsigned int, unsigned int> myHashMap( 1 );
    bool hasKey( true );

    size_t size( 0 );
    size = myHashMap.size();
    EXPECT_EQ( size, 0u );

    myHashMap.insert( 1, 10 );
    hasKey = myHashMap.hasKey( 1 );
    EXPECT_TRUE( hasKey );

    myHashMap.insert( 2, 10 );
    hasKey = myHashMap.hasKey( 2 );
    EXPECT_TRUE( hasKey );
}

TEST_F( THashMapTest, removeTest ) {
    bool success( false );
    size_t size( 0 );
    THashMap<unsigned int, unsigned int> myHashMap( 1 );

    success = myHashMap.remove( 1 );
    EXPECT_FALSE( success );

    myHashMap.insert( 1, 10 );
    myHashMap.insert( 2, 10 );
    myHashMap.insert( 3, 10 );
    size = myHashMap.size();
    EXPECT_EQ( size, 3u );

    success = myHashMap.remove( 2 );
    EXPECT_TRUE( success );
    size = myHashMap.size();
    EXPECT_EQ( size, 2u );

    success = myHashMap.remove( 1 );
    EXPECT_TRUE( success );
    size = myHashMap.size();
    EXPECT_EQ( size, 1u );

    success = myHashMap.remove( 3 );
    EXPECT_TRUE( success );
    size = myHashMap.size();
    EXPECT_EQ( size, 0u );
    EXPECT_TRUE( myHashMap.isEmpty() );

    success = myHashMap.remove( 1 );
    EXPECT_FALSE( success );

    success = myHashMap.hasKey( 1 );
    EXPECT_FALSE( success );
}

TEST_F( THashMapTest, removeOnlyOneTest ) {
    THashMap<unsigned int, unsigned int> myHashMap;
    myHashMap.insert( 1, 10 );
    bool success = myHashMap.remove( 1 );
    EXPECT_TRUE( success );

    success = myHashMap.hasKey( 1 );
    EXPECT_FALSE( success );
}

TEST_F( THashMapTest, HasKeyWhenCleared_ReturnsFalse ) {
    THashMap<unsigned int, unsigned int> myHashMap;

    myHashMap.clear();
    bool result = myHashMap.hasKey( 1 );

    EXPECT_FALSE( result );
}

TEST_F( THashMapTest, InitAccessCapacity_Successful ) {
    THashMap<unsigned int, unsigned int> myHashMap( 100 );
    EXPECT_EQ( 100u, myHashMap.capacity() );
}

TEST_F( THashMapTest, Reinit_Successful ) {
    THashMap<unsigned int, unsigned int> myHashMap( 100 );
    myHashMap.clear();
    myHashMap.init( 100 );

    EXPECT_EQ( 100u, myHashMap.capacity() );
    myHashMap.insert( 1, 10 );
    EXPECT_TRUE( myHashMap.hasKey( 1 ) );
}
