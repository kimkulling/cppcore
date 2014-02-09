#include <cppcore/Container/TList.h>

#include "gtest/gtest.h"

#include <sstream>
#include <iostream>
#include <vector>

using namespace CPPCore;

//-------------------------------------------------------------------------------------------------
///	@class		TListTest
///	@ingroup	UnitTest
///
///	@brief	The array tests.
//-------------------------------------------------------------------------------------------------
class TListTest : public testing::Test {
protected:
    //---------------------------------------------------------------------------------------------
    void createList( ui32 numEntries, TList<f32> &rDataList, std::vector<f32> &rValues ) {
		rValues.resize( 0 );
		rDataList.clear();
		for ( ui32 i=0; i<numEntries; ++i ) {
			f32 value =  i*1.0f ;
			rDataList.addBack( value );
			rValues.push_back( value );
		}
	}
};

//---------------------------------------------------------------------------------------------
TEST_F( TListTest, constructTest) {
	TList<f32> listTest;
	EXPECT_TRUE( listTest.isEmpty() );
	EXPECT_EQ( 0, listTest.size() );
}

//---------------------------------------------------------------------------------------------
TEST_F( TListTest, addBackTest) {
	TList<f32> listTest;
	listTest.addBack( 1.0f );
	listTest.addBack( 2.0f );
	listTest.addBack( 3.0f );

	EXPECT_EQ( 3, listTest.size() );
	EXPECT_TRUE( !listTest.isEmpty() ); 
}

//---------------------------------------------------------------------------------------------
TEST_F( TListTest, addFrontTest) {
	TList<f32> listTest;
	listTest.addFront( 1.0f );
	listTest.addFront( 2.0f );
	listTest.addFront( 3.0f );
		
	EXPECT_EQ( 3, listTest.size() );
	EXPECT_TRUE( !listTest.isEmpty() ); 
}

//---------------------------------------------------------------------------------------------
TEST_F( TListTest, copyTest ) {
	TList<f32> listTest;
	TList<f32> copyTest1( listTest );
	EXPECT_TRUE( copyTest1.isEmpty() );
	EXPECT_EQ( 0, copyTest1.size() );

	listTest.addBack( 1.0f );
	listTest.addBack( 2.0f );
	TList<f32> copyTest2( listTest );
	EXPECT_TRUE( !copyTest2.isEmpty() );
	EXPECT_EQ( 2, copyTest2.size() );
}

//---------------------------------------------------------------------------------------------
TEST_F( TListTest, accessTest ) {
	const ui32 numEntries = 10;
	TList<f32> listTest;
	std::vector<f32> values;
	createList( numEntries, listTest, values );

	EXPECT_EQ( numEntries, listTest.size() );
	EXPECT_TRUE( !listTest.isEmpty() ); 

	ui32 dataIdx = 0;
	for ( TList<f32>::Iterator it = listTest.begin(); it != listTest.end(); ++it ) {
		f32 listVal = *it;
		f32 orig = values[ dataIdx ];
		EXPECT_EQ( listVal, orig );
		++dataIdx;
	}
}

//---------------------------------------------------------------------------------------------
TEST_F( TListTest, clearTest ) {
	const ui32 numEntries = 10;
	TList<f32> listTest;
	std::vector<f32> values;
	createList( numEntries, listTest, values );

	listTest.clear();
	EXPECT_EQ( listTest.size(), 0 );
	EXPECT_TRUE( listTest.isEmpty() );
}

//---------------------------------------------------------------------------------------------
TEST_F( TListTest, removeTest )	{
	const ui32 numEntries = 10;
	TList<f32> listTest;
	std::vector<f32> values;

	createList( numEntries, listTest, values );
		
	for ( ui32 i=0; i<numEntries; ++i ) {
		const f32 value = listTest.front();
		EXPECT_EQ( value, values[ i ] );
		listTest.removeFront();
	}
}

//---------------------------------------------------------------------------------------------
TEST_F( TListTest, isEmptyTest ) {
	TList<f32> listTest;
	EXPECT_TRUE( listTest.isEmpty() );
	listTest.addBack( 1.0f );
	listTest.addBack( 2.0f );
	listTest.removeFront();
	listTest.removeFront();
	EXPECT_TRUE( listTest.isEmpty() );
}
	
//---------------------------------------------------------------------------------------------
TEST_F( TListTest, bug_IterateEmptyListTest ) {
	TList<f32> listTest;
	bool ok = true;
	try {
		for ( TList<f32>::Iterator it = listTest.begin(); it != listTest.end(); ++it );
	} catch ( ... )	{
		ok = false;
	}
	EXPECT_TRUE( ok );
}

//---------------------------------------------------------------------------------------------
