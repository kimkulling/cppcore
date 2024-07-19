/*-----------------------------------------------------------------------------------------------
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
-----------------------------------------------------------------------------------------------*/
#include <gtest/gtest.h>

#include <cppcore/Common/TSharedPtr.h>

using namespace ::cppcore;

class TSharedPtrTest : public ::testing::Test {
    // empty
};

TEST_F( TSharedPtrTest, createInstance_success ) {
    bool ok( true );
    try {
        int *ptr = new int;
        TSharedPtr<int> myPtr( ptr );
    } catch ( ... ) {
        ok = false;
    }
    EXPECT_TRUE( ok );
}

TEST_F( TSharedPtrTest, copyPtr_success ) {
    int *ptr = new int;
    TSharedPtr<int> myPtr1( ptr );
    TSharedPtr<int> myPtr2( myPtr1 );
    unsigned int refs1 = myPtr2.getRefs();
    EXPECT_EQ( 2U, refs1 );

    myPtr2.clear();
    unsigned int refs2 = myPtr1.getRefs();
    EXPECT_EQ( refs2, refs1-1 );
}

TEST_F( TSharedPtrTest, resetPtr_success ) {
    int *ptr = new int;
    TSharedPtr<int> myPtr1( ptr );

    myPtr1.reset( new int );
}
