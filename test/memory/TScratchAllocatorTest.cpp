#include <cppcore/Memory/TScratchAllocator.h>

#include <gtest/gtest.h>

using namespace cppcore;

class TScratchAllocatorTest : public testing::Test {};

TEST_F(TScratchAllocatorTest, CreateTest) {
    bool ok( true );
    try {
        ScratchAllocator myAllocator(1024);
    } catch ( ... ) {
        ok = false;
    }
    EXPECT_TRUE( ok );
}

TEST_F(TScratchAllocatorTest, AllocTest) {
    ScratchAllocator myAllocator(1024);
    char *ptr1 = myAllocator.alloc(512);
    EXPECT_NE(ptr1, nullptr);
    EXPECT_EQ(myAllocator.capacity(), 1024);
    EXPECT_EQ(myAllocator.freeMem(), 512);

    char *ptr2 = myAllocator.alloc(600);
    EXPECT_EQ(ptr2, nullptr);
}
