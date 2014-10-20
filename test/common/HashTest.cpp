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

#include <cppcore/Common/Hash.h>

#include "gtest/gtest.h"

using namespace CPPCore;

//---------------------------------------------------------------------------------------------
class HashTest : public testing::Test {
protected:
};

//---------------------------------------------------------------------------------------------
TEST_F( HashTest, CreateTest ) {
    Hash myHash1;
    EXPECT_EQ( myHash1.hashValue(), 0 );

    Hash myHash2( 10 );
    EXPECT_EQ( myHash2.hashValue(), 10 );

    Hash myHash3( "test" );
    EXPECT_NE( myHash3.hashValue(), 0 );
}

//---------------------------------------------------------------------------------------------
TEST_F( HashTest, MakeStringHashTest ) {
    Hash myHash;
    EXPECT_EQ(myHash.hashValue(), 0 );
    
    std::string value;
    value = ( "huhu1" );
    const int hash1 = myHash.toHash( value.c_str() );
    EXPECT_EQ( myHash.hashValue(), hash1 );
    EXPECT_NE( myHash.hashValue(), 0 );

    value = ( "huhu2" );
    const int hash2 = myHash.toHash( value.c_str() );
    EXPECT_EQ( myHash.hashValue(), hash2 );
    EXPECT_NE( myHash.hashValue(), 0 );

    value = ( "huhu3" );
    const int hash3 = myHash.toHash( value.c_str() );
    EXPECT_EQ( myHash.hashValue(), hash3 );
    EXPECT_NE( myHash.hashValue(), 0 );
}

//---------------------------------------------------------------------------------------------
