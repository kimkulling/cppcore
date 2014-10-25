/*
-------------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014 Kim Kulling

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

using namespace ::CPPCore;

class THashMapTest : public ::testing::Test {
};

TEST_F( THashMapTest, constructTest ) {
    bool ok( true );
    try {
        THashMap<unsigned int, unsigned int> myHashMap;
    } catch( ... ) {
        ok = false;
    }
    EXPECT_TRUE( ok );
}

TEST_F( THashMapTest, clearTest ) {
    THashMap<unsigned int, unsigned int> myHashMap( 1 );
    myHashMap.insert( 1, 10 );
    myHashMap.insert( 2, 10 );
    myHashMap.insert( 3, 10 );
    myHashMap.clear();
}

TEST_F( THashMapTest, insertTest ) {
    THashMap<unsigned int, unsigned int> myHashMap;
    bool hasKey( true );

    unsigned int size( 0 );
    size = myHashMap.size();
    EXPECT_EQ( size, 0 );

    hasKey = myHashMap.hasKey( 1 );
    EXPECT_FALSE( hasKey );
    
    myHashMap.insert( 1, 10 );
    hasKey = myHashMap.hasKey( 1 );
    EXPECT_TRUE( hasKey );

    size = myHashMap.size();
    EXPECT_EQ( size, 1 );

    unsigned int value = myHashMap.getValue( 1 );
    EXPECT_EQ( value, 10 );

    myHashMap.insert( 2, 10 );
    hasKey = myHashMap.hasKey( 2 );
    EXPECT_TRUE( hasKey );

    size = myHashMap.size();
    EXPECT_EQ( size, 2 );
}

TEST_F( THashMapTest, collideTest ) {
    THashMap<unsigned int, unsigned int> myHashMap( 1 );
    bool hasKey( true );

    unsigned int size( 0 );
    size = myHashMap.size();
    EXPECT_EQ( size, 0 );

    myHashMap.insert( 1, 10 );
    hasKey = myHashMap.hasKey( 1 );
    EXPECT_TRUE( hasKey );

    myHashMap.insert( 2, 10 );
    hasKey = myHashMap.hasKey( 2 );
    EXPECT_TRUE( hasKey );
}