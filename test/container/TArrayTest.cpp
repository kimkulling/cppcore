#include <cppcore/Container/TArray.h>

#include "gtest/gtest.h"

#include <sstream>
#include <iostream>

using namespace CPPCore;

static const ui32 ArraySize = 4;

static const f32  ArrayData[ ArraySize ] = {
	0.0f,
	1.0f,
	2.0f,
	3.0f
};

//-------------------------------------------------------------------------------------------------
///	@class		TArrayTest
///	@ingroup	UnitTest
///
///	@brief	The array tests.
//-------------------------------------------------------------------------------------------------
class TArrayTest : public testing::Test {
protected:
	void createArray( const f32 *pOrig, ui32 numItems, TArray<f32> &arrayInstance ) {
		for ( ui32 i=0; i<numItems; ++i ) {
			arrayInstance.add( pOrig[ i ] );
		}
	}

};

//---------------------------------------------------------------------------------------------
TEST_F( TArrayTest, constructTest ) {
	TArray<f32> arrayInstance;
	EXPECT_EQ( true, arrayInstance.isEmpty() );
    EXPECT_EQ( 0, arrayInstance.size() );
    EXPECT_EQ( arrayInstance.begin(), arrayInstance.end() );
}

//---------------------------------------------------------------------------------------------
TEST_F( TArrayTest, constructWithSizeTest) {
	TArray<f32> arrayInstance( 4 );
	EXPECT_EQ( 4, arrayInstance.size() );
}

//---------------------------------------------------------------------------------------------
TEST_F( TArrayTest, addTest) {
	TArray<f32> arrayInstance;
	arrayInstance.add( 0.0f );
	arrayInstance.add( 1.0f );

	EXPECT_EQ( 2, arrayInstance.size() );
	EXPECT_EQ( 0.0f, arrayInstance[ 0 ] );
	EXPECT_EQ( 1.0f, arrayInstance[ 1 ] );
}

//---------------------------------------------------------------------------------------------
TEST_F( TArrayTest, accessTest) {
	TArray<f32> arrayInstance;
	arrayInstance.add( 0.0f );
	arrayInstance.add( 1.0f );
		
	EXPECT_EQ( 0.0f, arrayInstance[ 0 ] );
	EXPECT_EQ( 1.0f, arrayInstance[ 1 ] );
}

//---------------------------------------------------------------------------------------------
TEST_F( TArrayTest, removeTest) {
	TArray<f32> arrayInstance;
	createArray( ArrayData, ArraySize, arrayInstance );

	std::stringstream stream;
	static const ui32 Size = 3;
	arrayInstance.remove( 1 );
	EXPECT_EQ( Size, arrayInstance.size() );
	f32 expectedResult[ Size ] = { 0.0f, 2.0f, 3.0f };
	bool equal = true;
	for ( ui32 i=0; i<Size; ++i ) {
		if ( arrayInstance[ i ] != expectedResult[ i ] ) {
			stream << "error in index " << i << std::endl;
			equal = false;
			break;
		}
	}
    EXPECT_TRUE( equal ) << stream.str();
}

//---------------------------------------------------------------------------------------------
TEST_F( TArrayTest, removeBackTest) {
	TArray<f32> arrayInstance;
	createArray( ArrayData, ArraySize, arrayInstance );

	arrayInstance.removeBack();
	EXPECT_EQ( 3, arrayInstance.size() );
	EXPECT_EQ( 2.0f, arrayInstance[ 2 ] );
}

//---------------------------------------------------------------------------------------------
TEST_F( TArrayTest, resizeTest ) {
	TArray<f32> arrayInstance;
	EXPECT_EQ( 0, arrayInstance.size() );

	arrayInstance.resize( 5 );
	EXPECT_EQ( 5, arrayInstance.size() );
}

//---------------------------------------------------------------------------------------------
TEST_F( TArrayTest, moveTest ) {
    TArray<f32> arrayInstance;
    arrayInstance.add( 1.0f );
    arrayInstance.add( 2.0f );
    arrayInstance.add( 3.0f );
    arrayInstance.move( 1, 3 );
}

//---------------------------------------------------------------------------------------------
TEST_F( TArrayTest, reserveTest ) {
	TArray<f32> arrayInstance;
	EXPECT_EQ( 0, arrayInstance.capacity() );

	arrayInstance.reserve( 5 );
	EXPECT_EQ( 5, arrayInstance.capacity() );

	arrayInstance.reserve( 2000 );
	EXPECT_EQ( 2000, arrayInstance.capacity() );
}

//---------------------------------------------------------------------------------------------
TEST_F( TArrayTest, iterateTest ) {
	TArray<f32> arrayInstance;
	createArray( ArrayData, ArraySize, arrayInstance );

	ui32 i( 0 );
	for ( TArray<f32>::Iterator it = arrayInstance.begin(); it != arrayInstance.end(); ++it ) {
		++i;
	}
	EXPECT_EQ( i, arrayInstance.size() );
}

//---------------------------------------------------------------------------------------------
TEST_F( TArrayTest, preIncIterateTest ) {
	TArray<f32> arrayInstance;
	createArray( ArrayData, ArraySize, arrayInstance );

	bool ok = true;
	try {
		ui32 i=0;
		for ( TArray<f32>::Iterator it = arrayInstance.begin(); it != arrayInstance.end(); ++it ) {
			f32 tmp = *it;
			EXPECT_EQ( tmp, ArrayData[ i ] );
			++i;
		}
	}
	catch (...)	{
		ok = false;	
	}
	EXPECT_TRUE( ok );
}

//---------------------------------------------------------------------------------------------
TEST_F( TArrayTest, postIncIterateTest ) {
	TArray<f32> arrayInstance;
	createArray( ArrayData, ArraySize, arrayInstance );

	bool ok = true;
	try {
		ui32 i=0;
		for ( TArray<f32>::Iterator it = arrayInstance.begin(); it != arrayInstance.end(); it++ ) {
			f32 tmp = *it;
			EXPECT_EQ( tmp, ArrayData[ i ] );
			++i;
		}
	}
	catch (...) {
		ok = false;	
	}
	EXPECT_TRUE( ok );
}

//---------------------------------------------------------------------------------------------
TEST_F( TArrayTest, findTest )	{
	TArray<f32> arrayInstance;
	arrayInstance.add( 0.0f );
	arrayInstance.add( 1.0f );
	arrayInstance.add( 2.0f );
	arrayInstance.add( 3.0f );
	EXPECT_EQ( 4, arrayInstance.size() );

	TArray<f32>::Iterator it = arrayInstance.find( 1.0f );
	EXPECT_NE( it, arrayInstance.end() );
	EXPECT_EQ( *it, 1.0f );
}

//---------------------------------------------------------------------------------------------
//	Crash when iterating an empty array.
//---------------------------------------------------------------------------------------------
TEST_F( TArrayTest, bug_IterateEmptyListTest )	{
	TArray<f32> arrayInstance;
	bool ok = true;
	try {
		for ( TArray<f32>::Iterator it = arrayInstance.begin(); it != arrayInstance.end(); ++it );
	}
	catch ( ... ) {
		ok = false;
	}
	EXPECT_TRUE( ok );
}

//---------------------------------------------------------------------------------------------
//	Heap corruption after grow.
//---------------------------------------------------------------------------------------------
TEST_F( TArrayTest, bug_AddHeapCorruptTest ) {
	TArray<f32> arrayInstance;
	for ( ui32 i=0; i<50; ++i ) {
		arrayInstance.add( (f32) i );
	}
}
	
//---------------------------------------------------------------------------------------------
