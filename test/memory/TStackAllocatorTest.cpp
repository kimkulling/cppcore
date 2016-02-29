//

#include <cppcore/Memory/TStackAllocator.h>

#include "gtest/gtest.h"

using namespace CPPCore;

//---------------------------------------------------------------------------------------------
class TStackAllocatorTest : public testing::Test {
protected:
};

TEST_F( TStackAllocatorTest, CreateTest ) {
    bool ok( true );
    try {
        TStackAllocator<int> myAllocator( 1024 );
    }
    catch ( ... ) {
        ok = false;
    }
    EXPECT_TRUE( ok );
}

TEST_F( TStackAllocatorTest, AllocReleaseTest ) {
    TStackAllocator<int> myAllocator( 1024 );

    int *myArray = myAllocator.alloc( 10 );
    EXPECT_TRUE( nullptr != myArray );

    myAllocator.release( myArray );
}
