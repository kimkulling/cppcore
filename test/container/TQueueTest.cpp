#include <cppcore/Container/TQueue.h>

#include "gtest/gtest.h"

using namespace CPPCore;

//-------------------------------------------------------------------------------------------------
///	@class		TQueueTest
///	@ingroup	UnitTest
///
///	@brief	The queue tests.
//-------------------------------------------------------------------------------------------------
class TQueueTest : public testing::Test {
public:
	//---------------------------------------------------------------------------------------------
	virtual void setUp() { 
		// empty
	}

	//---------------------------------------------------------------------------------------------
	virtual void tearDown()	{ 
		// empty
	}
};

//---------------------------------------------------------------------------------------------
TEST_F( TQueueTest, constructTest) {
    TQueue<float> f32Queue;
    EXPECT_TRUE( f32Queue.isEmpty() );

    TQueue<float> copy( f32Queue );
    EXPECT_EQ( copy, f32Queue );
    EXPECT_TRUE( copy.isEmpty() );
}

//---------------------------------------------------------------------------------------------
TEST_F( TQueueTest, enqueueDequeueTest ) {
	TQueue<f32> f32Queue;
	bool hasItems = false;
	f32 val = 0.0f;

	f32Queue.enqueue( 0.0f );
	EXPECT_EQ( f32Queue.size(), 1 );
	EXPECT_TRUE( !f32Queue.isEmpty() );
	hasItems = f32Queue.dequeue( val );
	EXPECT_TRUE( !hasItems );
	EXPECT_EQ( 0.0f, val );

	f32Queue.enqueue( 0.0f );
	f32Queue.enqueue( 1.0f );
	f32Queue.enqueue( 2.0f );
	EXPECT_EQ( f32Queue.size(), 3 );

	hasItems = f32Queue.dequeue( val );
	EXPECT_EQ( val, 0.0f );
	EXPECT_TRUE( hasItems );
	EXPECT_EQ( f32Queue.size(), 2 );

	hasItems = f32Queue.dequeue( val );
	EXPECT_EQ( val, 1.0f );
	EXPECT_TRUE( hasItems );
	EXPECT_EQ( f32Queue.size(), 1 );

	hasItems = f32Queue.dequeue( val );
	EXPECT_EQ( val, 2.0f );
	EXPECT_EQ( f32Queue.size(), 0 );
	EXPECT_TRUE( !hasItems );
	EXPECT_TRUE( f32Queue.isEmpty() );
}

//---------------------------------------------------------------------------------------------
TEST_F( TQueueTest, sizeTest ) {
	TQueue<f32> f32Queue;
	EXPECT_EQ( f32Queue.size(), 0 );

	f32Queue.enqueue( 0.0f );
	f32Queue.enqueue( 1.0f );
	f32Queue.enqueue( 2.0f );
	EXPECT_EQ( f32Queue.size(), 3 );

	f32 val;
	bool hasItems = f32Queue.dequeue( val );
	EXPECT_TRUE( hasItems );
	EXPECT_EQ( val, 0.0f );
	EXPECT_EQ( f32Queue.size(), 2 );
}

//---------------------------------------------------------------------------------------------
TEST_F( TQueueTest, clearTest )	{
	TQueue<f32> f32Queue;

	f32Queue.enqueue( 0.0f );
	f32Queue.enqueue( 1.0f );
	f32Queue.enqueue( 2.0f );
	EXPECT_EQ( f32Queue.size(), 3 );

	f32Queue.clear();
	EXPECT_TRUE( f32Queue.isEmpty() );
	EXPECT_EQ( 0, f32Queue.size() );
}

//---------------------------------------------------------------------------------------------
