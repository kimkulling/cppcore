#pragma once

/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014 Kim Kulling

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
#ifndef CPPCORE_COMMON_TSTRINGBASE_H_INC
#define CPPCORE_COMMON_TSTRINGBASE_H_INC

#include <cppcore/CPPCoreCommon.h>

#include "string.h"

namespace CPPCore {

//-------------------------------------------------------------------------------------------------
template<class T>
inline
T *alloc( unsigned int size ) {
    return new T[ size ];
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
void dealloc( T *ptr ) {
    delete [] ptr;
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
static unsigned int countChars( T *ptr ) {
    if ( !ptr ) {
        return 0;
    }
        
    return ( ::strlen( ptr ) );
}

//-------------------------------------------------------------------------------------------------
///	@class		TStringBase
///	@ingroup    CPPCore
///
///	@brief  This class is used to describe the inner data of a string.
//-------------------------------------------------------------------------------------------------
template<class T>
class TStringBase {
public:
    /// @brief  The default class constructor.
    TStringBase();

    /// @brief  The class constructor with a pointer showing to the data buffer.
    /// @param  pPtr        [in] The data buffer.
    TStringBase( const T *pPtr );

    /// @brief  The class destructor.
    ~TStringBase();

    /// @brief  Helper method to copy data into the string.
    /// @param  base        [inout] The string data to copy in.
    /// @param  pPtr        [in] The data source.
    static void copyFrom( TStringBase<T> &base, const T *pPtr );

    T *m_pStringBuffer;
    size_t m_size;
    size_t m_capacity;
};

//-------------------------------------------------------------------------------------------------
template<class T>
inline
TStringBase<T>::TStringBase()
: m_pStringBuffer( nullptr )
, m_size( 0 )
, m_capacity( 0 ) {
    // empty
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
TStringBase<T>::TStringBase( const T *pPtr ) 
: m_pStringBuffer( nullptr )
, m_size( 0 )
, m_capacity( 0 ) {
    copyFrom( *this, pPtr );
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
TStringBase<T>::~TStringBase() {
    if ( m_pStringBuffer ) {
        dealloc( m_pStringBuffer );
        m_pStringBuffer = nullptr;
    }
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
void TStringBase<T>::copyFrom( TStringBase<T> &base, const T *pPtr ) {
    if ( pPtr ) {
        base.m_size = countChars( pPtr );
        if ( base.m_size ) {
            base.m_capacity = base.m_size + 1;
            base.m_pStringBuffer = alloc<T>( base.m_capacity );
            strncpy( base.m_pStringBuffer, pPtr, base.m_size );
            base.m_pStringBuffer[ base.m_size ] = '\0';
        }
    }
}

//-------------------------------------------------------------------------------------------------

} // Namespace CPPCore

#endif // CPPCORE_COMMON_TSTRINGBASE_H_INC
