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
#pragma once
#ifndef CPPCORE_THASHMAP_H_INC
#define CPPCORE_THASHMAP_H_INC

#include <cppcore/Common/Hash.h>

namespace CPPCore {

//-------------------------------------------------------------------------------------------------
///	@class		THashMap
///	@ingroup	CPPCore
///
///	@brief
//-------------------------------------------------------------------------------------------------
template<class T, class U> 
class THashMap {
public:
    static const size_t InitSize = 1024;

public:
    THashMap( size_t init = InitSize );
    ~THashMap();
    size_t size() const;
    bool isEmpty() const;
    void clear();
    void insert( const T &key, const U &value );
    bool remove( const T &key );
    U &operator [] ( const T &key ) const;

private:
    struct Node {
        T m_hash;
        U m_value;
        Node *m_next;

        Node();
        void insert( T hash, const U &value ) {
            Node *next( m_next );
            while( next->m_next ) {
                next = next->m_next;
            }
            next->m_next = new Node;
            next->m_next->m_hash = hash;
            next->m_next->m_value = value;
        }
    };

    Node *m_buffer;
    Node *m_first;
    Node *m_last;
    size_t m_numItems;
    size_t m_buffersize;
};

//-------------------------------------------------------------------------------------------------
template<class T, class U>
inline
THashMap<T, U>::THashMap( size_t init )
: m_buffer( nullptr )
, m_first( nullptr )
, m_last( nullptr )
, m_numItems( 0 ),
m_buffersize( 0 ) {
    m_buffer = new Node[ init ];
    m_first = m_buffer;
    m_last = &m_buffer[InitSize-1] + 1;
    m_buffersize = init;
}

//-------------------------------------------------------------------------------------------------
template<class T, class U>
inline
THashMap<T, U>::~THashMap() {
    clear();
}

//-------------------------------------------------------------------------------------------------
template<class T, class U>
inline
size_t THashMap<T, U>::size() const {
    return m_numItems;
}

//-------------------------------------------------------------------------------------------------
template<class T, class U>
inline
bool THashMap<T, U>::isEmpty() const {
    return ( 0 == m_numItems );
}

//-------------------------------------------------------------------------------------------------
template<class T, class U>
inline
void THashMap<T, U>::clear() {
    delete[] m_buffer;
    m_buffer = nullptr;
    m_first = nullptr;
    m_last = nullptr;
    m_numItems = 0;
    m_buffersize = 0;
}

//-------------------------------------------------------------------------------------------------
template<class T, class U>
inline
void THashMap<T, U>::insert( const T &key, const U &value ) {
    const unsigned int hash( Hash::toHash( key, m_buffersize ) );

    if( m_buffer[ hash ].m_hash == 0 ) {
        m_buffer[ hash ].m_hash = hash;
        m_buffer[ hash ].m_value = value;
    } else {
        m_buffer[ hash ].insert( key, value );
    }
}

//-------------------------------------------------------------------------------------------------
template<class T, class U>
inline
bool THashMap<T, U>::remove( const T &key ) {

}
    
//-------------------------------------------------------------------------------------------------
template<class T, class U>
inline
U &THashMap<T, U>::operator [] ( const T &key ) const {
    unsigned int pos( Hash::toHash( key, m_buffersize ) );
    if( m_buffer[ pos ].m_hash == pos ) {

    }
}

//-------------------------------------------------------------------------------------------------
template<class T, class U>
inline
THashMap<T, U>::Node::Node()
: m_hash( 0 )
, m_value()
, m_next( nullptr ) {
    // empty
}

//-------------------------------------------------------------------------------------------------

} // Namespace CPPCore

#endif // CPPCORE_THASHMAP_H_INC
