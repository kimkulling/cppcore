/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2017 Kim Kulling

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
-----------------------------------------------------------------------------------------------*/
#include <cppcore/Common/CString.h>

#include "gtest/gtest.h"

using namespace CPPCore;

class StringTest : public testing::Test {
protected:
    // empty
};

TEST_F( StringTest, DefaultConstructor ) {
    CString str;
    EXPECT_EQ( 0, str.size() );
    EXPECT_EQ( true, str.isEmpty() );
}

TEST_F( StringTest, PtrConstructor ) {
    const char buffer[] = "this is a test\0";
    CString str( buffer );
    EXPECT_EQ( 14U, str.size() );
    EXPECT_FALSE( str.isEmpty() );
    int res( strncmp( buffer, str.c_str(), str.size() ) );
    EXPECT_EQ( 0, res );
}

TEST_F( StringTest, CopyConstructor ) {
    CString str1( "test1" );
    CString str2( str1 );
    EXPECT_EQ( str1, str2 );

    CString str3( "test1" );
    CString str4( str3 );
    EXPECT_EQ( str3, str4 );
}

TEST_F( StringTest, AssignmentOperator ) {
    CString str1( "test1" );
    CString str2( "test2" );
    str1 = str2;
    EXPECT_EQ( CString( "test2" ), str2 );
    EXPECT_EQ( str1, str2 );

    CString emptystr;
    str1 = emptystr;
    EXPECT_TRUE( str1.isEmpty() );
}

TEST_F( StringTest, CompareOperator ) {
    CString str1( "test1" );
    CString str2( "test2" );
    EXPECT_NE( str1, str2 );
    EXPECT_EQ( str1, str1 );

    CString str3( "test1" );
    EXPECT_EQ( str1, str3 );
}
