/*
-------------------------------------------------------------------------------------------------
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
-------------------------------------------------------------------------------------------------
*/
#include <cppcore/Common/CString.h>

#include <cassert>

namespace CPPCore {

char *getTrans( unsigned int /* id */ ) {
    return nullptr;
}

CString::CString()
: m_string() {
    // empty
}

CString::CString( const char *pStr )
: m_string( pStr ) {

}

CString::CString( const CString &rhs )
: m_string() {
    TStringBase<char>::copyFrom( m_string, rhs.c_str() );
}

CString::~CString() {

}

bool CString::isEmpty() const {
    return ( m_string.m_size == 0 );
}

size_t CString::size() const {
    return m_string.m_size;
}

void CString::clear() {
    delete [] m_string.m_pStringBuffer;
    m_string.m_pStringBuffer = nullptr;
    m_string.m_capacity = 0;
    m_string.m_size = 0;
}

const char* CString::c_str() const {
    return m_string.m_pStringBuffer;
}

char CString::operator [] ( size_t idx ) const {
    assert( idx < m_string.m_size );

    return m_string.m_pStringBuffer[ idx ];
}

bool CString::operator == ( const CString &rhs ) const {
    if ( m_string.m_size != rhs.size() ) {
        return false;
    }

    return ( 0 == strncmp( m_string.m_pStringBuffer, rhs.c_str(), rhs.size() ) );
}

bool CString::operator != ( const CString &rhs ) const {
    return !( *this == rhs );
}

CString &CString::operator = ( const CString &rhs ) {
    if ( m_string.m_capacity > rhs.m_string.m_size ) {
        ::memset( m_string.m_pStringBuffer, '\0', m_string.m_capacity );
        strncpy( m_string.m_pStringBuffer, rhs.c_str(), rhs.size() );
        m_string.m_size = rhs.size();
        return *this;
    }

    clear();
    m_string.m_size =  rhs.size() + 1;
    m_string.m_pStringBuffer = new char[ m_string.m_size ];
    strncpy( m_string.m_pStringBuffer, rhs.c_str(), rhs.size() );
    m_string.m_pStringBuffer[ m_string.m_size ] = '\0';

    return *this;
}

}
