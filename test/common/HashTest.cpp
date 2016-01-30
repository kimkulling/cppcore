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

    Hash myHash3( "test", 7 );
    EXPECT_NE( myHash3.hashValue(), (unsigned int) 0 );
}

//---------------------------------------------------------------------------------------------
TEST_F( HashTest, MakeStringHashTest ) {
    static const unsigned int Base = 7;
    Hash myHash_empty;
    EXPECT_EQ( myHash_empty.hashValue(), 0 );
    
    std::string value;
    value = ( "huhu1" );
    const unsigned int hash1 = Hash::toHash( value.c_str(), Base );
    EXPECT_NE( hash1, ( unsigned int ) 0 );
    EXPECT_LE( hash1, Base );

    value = ( "huhu2" );
    const unsigned int hash2 = Hash::toHash( value.c_str(), Base );
    EXPECT_NE( hash2, ( unsigned int ) 0 );
    EXPECT_LE( hash2, Base );

    value = ( "huhu3" );
    const unsigned int hash3 = Hash::toHash( value.c_str(), Base );
    EXPECT_NE( hash3, ( unsigned int ) 0 );
    EXPECT_LE( hash3, Base );

    Hash myHash_inited( value.c_str(), Base );
    EXPECT_EQ( myHash_inited.hashValue(), hash3 );
}
//---------------------------------------------------------------------------------------------
TEST_F( HashTest, MakeUIntHashTest ) {
    static const unsigned int Base = 7;
    Hash myHash_empty;
    EXPECT_EQ( myHash_empty.hashValue(), 0 );

    unsigned int value = 17;
    const unsigned int hash1 = Hash::toHash( value, Base );
    EXPECT_NE( hash1, ( unsigned int ) 0 );
    EXPECT_LE( hash1, Base );

    value = 27;
    const unsigned int hash2 = Hash::toHash( value, Base );
    EXPECT_NE( hash2, ( unsigned int ) 0 );
    EXPECT_LE( hash2, Base );

    value = 37;
    const unsigned int hash3 = Hash::toHash( value, Base );
    EXPECT_NE( hash3, ( unsigned int ) 0 );
    EXPECT_LE( hash3, Base );

    Hash myHash_inited( value, Base );
    EXPECT_EQ( myHash_inited.hashValue(), hash3 );
}

//---------------------------------------------------------------------------------------------
