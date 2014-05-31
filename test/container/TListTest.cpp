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
    void createList( size_t numEntries, TList<float> &rDataList, std::vector<float> &rValues ) {
		rValues.resize( 0 );
		rDataList.clear();
        for( size_t i = 0; i<numEntries; ++i ) {
            float value = i*1.0f;
			rDataList.addBack( value );
			rValues.push_back( value );
		}
	}
};

//---------------------------------------------------------------------------------------------
TEST_F( TListTest, constructTest) {
    TList<float> listTest;
	EXPECT_TRUE( listTest.isEmpty() );
	EXPECT_EQ( 0, listTest.size() );
}

//---------------------------------------------------------------------------------------------
TEST_F( TListTest, addBackTest) {
    TList<float> listTest;
	listTest.addBack( 1.0f );
	listTest.addBack( 2.0f );
	listTest.addBack( 3.0f );

	EXPECT_EQ( 3, listTest.size() );
	EXPECT_TRUE( !listTest.isEmpty() ); 
}

//---------------------------------------------------------------------------------------------
TEST_F( TListTest, addFrontTest) {
    TList<float> listTest;
	listTest.addFront( 1.0f );
	listTest.addFront( 2.0f );
	listTest.addFront( 3.0f );
		
	EXPECT_EQ( 3, listTest.size() );
	EXPECT_TRUE( !listTest.isEmpty() ); 
}

//---------------------------------------------------------------------------------------------
TEST_F( TListTest, copyTest ) {
    TList<float> listTest;
    TList<float> copyTest1( listTest );
	EXPECT_TRUE( copyTest1.isEmpty() );
	EXPECT_EQ( 0, copyTest1.size() );

	listTest.addBack( 1.0f );
	listTest.addBack( 2.0f );
    TList<float> copyTest2( listTest );
	EXPECT_TRUE( !copyTest2.isEmpty() );
	EXPECT_EQ( 2, copyTest2.size() );
}

//---------------------------------------------------------------------------------------------
TEST_F( TListTest, accessTest ) {
	const size_t numEntries = 10;
    TList<float> listTest;
    std::vector<float> values;
	createList( numEntries, listTest, values );

	EXPECT_EQ( numEntries, listTest.size() );
	EXPECT_TRUE( !listTest.isEmpty() ); 

	size_t dataIdx = 0;
    for( TList<float>::Iterator it = listTest.begin( ); it != listTest.end( ); ++it ) {
        float listVal = *it;
        float orig = values[ dataIdx ];
		EXPECT_EQ( listVal, orig );
		++dataIdx;
	}
}

//---------------------------------------------------------------------------------------------
TEST_F( TListTest, clearTest ) {
	const size_t numEntries = 10;
    TList<float> listTest;
    std::vector<float> values;
	createList( numEntries, listTest, values );

	listTest.clear();
	EXPECT_EQ( listTest.size(), 0 );
	EXPECT_TRUE( listTest.isEmpty() );
}

//---------------------------------------------------------------------------------------------
TEST_F( TListTest, removeTest )	{
	const size_t numEntries = 10;
    TList<float> listTest;
    std::vector<float> values;

	createList( numEntries, listTest, values );
		
	for ( size_t i=0; i<numEntries; ++i ) {
        const float value = listTest.front( );
		EXPECT_EQ( value, values[ i ] );
		listTest.removeFront();
	}
}

//---------------------------------------------------------------------------------------------
TEST_F( TListTest, isEmptyTest ) {
    TList<float> listTest;
	EXPECT_TRUE( listTest.isEmpty() );
	listTest.addBack( 1.0f );
	listTest.addBack( 2.0f );
	listTest.removeFront();
	listTest.removeFront();
	EXPECT_TRUE( listTest.isEmpty() );
}
	
//---------------------------------------------------------------------------------------------
TEST_F( TListTest, bug_IterateEmptyListTest ) {
    TList<float> listTest;
	bool ok = true;
	try {
        for( TList<float>::Iterator it = listTest.begin( ); it != listTest.end( ); ++it );
	} catch ( ... )	{
		ok = false;
	}
	EXPECT_TRUE( ok );
}

//---------------------------------------------------------------------------------------------
