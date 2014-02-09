#include <cppcore/Common/CString.h>

#include "gtest/gtest.h"

using namespace CPPCore;

//---------------------------------------------------------------------------------------------
class StringTest : public testing::Test {
protected:
};

//---------------------------------------------------------------------------------------------
TEST_F( StringTest, DefaultConstructor ) {
    CString str;
    EXPECT_EQ( 0, str.size() );
    EXPECT_EQ( true, str.isEmpty() );
}

//---------------------------------------------------------------------------------------------
TEST_F( StringTest, PtrConstructor ) {
    const char buffer[] = "this is a test\0";
    CString str( buffer );
    EXPECT_EQ( 14, str.size() );
    EXPECT_EQ( false, str.isEmpty() );
    i32 res( strncmp( buffer, str.c_str(), str.size() ) );
    EXPECT_EQ( 0, res );
}

//---------------------------------------------------------------------------------------------
TEST_F( StringTest, CopyConstructor ) {
    CString str1( "test1" );
    CString str2( str1 );
    EXPECT_EQ( str1, str2 );

    CString str3( "test1" );
    CString str4( str3 );
    EXPECT_EQ( str3, str4 );
}

//---------------------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------------------
TEST_F( StringTest, CompareOperator ) {
    CString str1( "test1" );
    CString str2( "test2" );
    EXPECT_NE( str1, str2 );
    EXPECT_EQ( str1, str1 );

    CString str3( "test1" );
    EXPECT_EQ( str1, str3 );

}

//---------------------------------------------------------------------------------------------
