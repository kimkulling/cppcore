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

#include <cppcore/Common/Variant.h>

using namespace cppcore;

//-------------------------------------------------------------------------------------------------
///	@class		::VariantTest
///	@ingroup	Test
///
///	@brief	This class implements the variant unit-tests.
//-------------------------------------------------------------------------------------------------
class VariantTest : public testing::Test {
protected:
    int *createInt( size_t buffersize ) {
        int *pData = new int[ buffersize ];
        for ( size_t i=0; i<buffersize; i++ ) {
            pData[ i ] = ( int ) i * 1;
        }

        return pData;
    }

    float *createFloatData( size_t buffersize )	{
        float *pData = new float[ buffersize ];
        for ( size_t i=0; i<buffersize; i++ ) {
            pData[ i ] = (float)i * 1.0f;
        }
        
        return pData;		
    }

    bool validateIntData( size_t buffersize, int *pData, int *pRes ) {
        bool equal = true;
        for( size_t i = 0; i<buffersize; i++ ) {
            if ( *pRes != pData[ i ] ) {
                equal = false;
                break;
            }
            ++pRes;
        }
        return equal;
    }

    bool validateFloatData( size_t buffersize, float *pData, float *pRes ) {
        bool equal = true;
        for( size_t i = 0; i<buffersize; i++ ) {
            if ( *pRes != pData[ i ] ) {
                equal = false;
                break;
            }
            ++pRes;
        }
        return equal;
    }
};
    
TEST_F( VariantTest, createTest ) {
    int data = 1;
    Variant test1( Variant::Int, (void*)&data, 1 ); 
    EXPECT_TRUE ( true );

    Variant test2;
    EXPECT_TRUE ( true );
        
    Variant *pTest3 = new Variant;
    delete pTest3;
    EXPECT_TRUE( true );
}
    
TEST_F( VariantTest, copyTest ) {
    int data = 1;
    Variant test1( Variant::Int, (void*)&data, 1 ); 
    EXPECT_TRUE ( true );

    Variant test2( test1 );
    EXPECT_EQ( test2, test1 );
}

TEST_F( VariantTest, accessIntTest ) {
    int data = 1;
    Variant test( Variant::Int, (void*)&data, 1 ); 

    int res = test.getInt( );
    EXPECT_EQ ( res, data );

    data = 2;
    test.setInt( data );
    res = test.getInt();
    EXPECT_EQ ( res, data );
}
    
TEST_F( VariantTest, accessInt3Test ) {
    static const size_t bufferSize = 3;
    int *pData = createInt( bufferSize );
    Variant test( Variant::Int3, (void*) pData, bufferSize ); 

    int *pRes = test.getInt3( );
    EXPECT_NE( nullptr, pRes );
        
    EXPECT_TRUE( validateIntData( bufferSize, pData, pRes ) );
        
    delete [] pData;
}

TEST_F( VariantTest, accessInt4Test ) {
    const size_t bufferSize = 4;
    int *pData = createInt( bufferSize );
    Variant test( Variant::Int4, (void*) pData, bufferSize ); 

    int *pRes = test.getInt4( );
    EXPECT_NE( nullptr, pRes );
        
    EXPECT_TRUE( validateIntData( bufferSize, pData, pRes ) );
    delete [] pData;
}

TEST_F( VariantTest, accessFloatTest ) {
    float data = 1.0f;
    Variant test( Variant::Float, (void*)&data, 1 ); 

    float res = test.getFloat( );
    EXPECT_EQ( res, data );

    data = 2.0f;
    test.setFloat( data );
    res = test.getFloat();
    EXPECT_EQ( res, data );
}

TEST_F( VariantTest, accessFloat3Test )	{
    const size_t bufferSize = 3;
    float *pData = createFloatData( bufferSize );
    Variant test( Variant::Float3, (void*) pData, bufferSize ); 

    float *pRes = test.getFloat3( );
    EXPECT_NE( pRes, nullptr );
        
    EXPECT_TRUE( validateFloatData( bufferSize, pData, pRes ) );
        
    delete [] pData;
}

TEST_F( VariantTest, accessFloat4Test ) {
    const size_t bufferSize = 4;
    float *pData = createFloatData( bufferSize );
    Variant test( Variant::Float4, (void*) pData, bufferSize ); 

    float *pRes = test.getFloat4( );
    EXPECT_NE( pRes, nullptr );

    validateFloatData( bufferSize, pData, pRes );

    float data[ 4 ] = {
        1.0f, 2.0f, 3.0f, 4.0f
    };
    test.setFloat4( data[ 0 ], data[ 1 ], data[ 2 ], data[ 3 ] );
    pRes = test.getFloat4();
    EXPECT_TRUE( validateFloatData( 4, data, pRes ) );

    delete [] pData;
}
    
TEST_F( VariantTest, accessBooleanTest ) {
    bool value( true );
    Variant test( value );

    EXPECT_EQ( test.getBool(), value );

    test.setBool( false );
    EXPECT_EQ( test.getBool(), false );

    Variant test1( test );
    EXPECT_EQ( test1, test );
}
