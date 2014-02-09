#pragma once
#ifndef CPPCORE_COMMON_TSTRINGBASE_H_INC
#define CPPCORE_COMMON_TSTRINGBASE_H_INC

#include <cppcore/CPPCoreCommon.h>

#include "string.h"

namespace CPPCore {

template<class T>
inline
T *alloc( ui32 size ) {
    return new T[ size ];
}

template<class T>
inline
void dealloc( T *ptr ) {
    delete [] ptr;
}

template<class T>
inline
static ui32 countChars( T *ptr ) {
    if ( !ptr ) {
        return 0;
    } else {
        return ( ::strlen( ptr ) );
    }
}


template<class T>
class DLL_CPPCORE_EXPORT TStringBase {
public:
    TStringBase();
    TStringBase( const T *pPtr );
    ~TStringBase();
    static void copyFrom( TStringBase<T> &base, const T *pPtr );

    T *m_pStringBuffer;
    ui32 m_size;
    ui32 m_capacity;
};

template<class T>
inline
TStringBase<T>::TStringBase()
: m_pStringBuffer( nullptr )
, m_size( 0 )
, m_capacity( 0 ) {
    // empty
}

template<class T>
inline
TStringBase<T>::TStringBase( const T *pPtr ) 
: m_pStringBuffer( nullptr )
, m_size( 0 )
, m_capacity( 0 ) {
    copyFrom( *this, pPtr );
}

template<class T>
inline
TStringBase<T>::~TStringBase() {
    if ( m_pStringBuffer ) {
        dealloc( m_pStringBuffer );
        m_pStringBuffer = nullptr;
    }
}

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

}

#endif // CPPCORE_COMMON_TSTRINGBASE_H_INC
