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
    static const size_t       InitSize = 1024;
    static const unsigned int UnsetNode = 999999999;

public:
    THashMap( size_t init = InitSize );
    ~THashMap();
    size_t size() const;
    bool isEmpty() const;
    void clear();
    void insert( const T &key, const U &value );
    bool remove( const T &key );
    bool hasKey( const T &key );
    U &getValue( const T &key ) const;
    U &operator [] ( const T &key ) const;

private:
    struct Node {
        T m_key;
        U m_value;
        Node *m_next;

        Node();
        ~Node();
        void append( T key, const U &value ) {
            if( m_key == UnsetNode ) {
                m_key = key;
                m_value = value;
                return;
            }

            Node *current( m_next );
            if( current ) {
                // already collisions, traverse
                while( current->m_next ) {
                    current = current->m_next;
                }
                current->m_next = new Node;
                current->m_next->m_key = key;
                current->m_next->m_value = value;
            } else {
                // first collision
                m_next = new Node;
                current = m_next;
                current->m_key = key;
                current->m_value = value;
            }
        }
    };

    Node *m_buffer;
    Node *m_first;
    Node *m_current;
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
, m_current( nullptr )
, m_last( nullptr )
, m_numItems( 0 )
, m_buffersize( 0 ) {
    m_buffer = new Node[ init ];
    m_first = m_buffer;
    m_last = &m_buffer[ InitSize-1 ] + 1;
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
    for( size_t i = 0; i < m_buffersize; ++i ) {
        if( m_buffer[ i ].m_next ) {
            Node *current( m_buffer[ i ].m_next ), *tmp( nullptr );
            while( current ) {
                tmp = current;
                current = current->m_next;
                delete tmp;
            }
        }
    }

    delete[] m_buffer;
    m_buffer = nullptr;
    m_first = nullptr;
    m_current = nullptr;
    m_last = nullptr;
    m_numItems = 0;
    m_buffersize = 0;
}

//-------------------------------------------------------------------------------------------------
template<class T, class U>
inline
void THashMap<T, U>::insert( const T &key, const U &value ) {
    const unsigned int hash( Hash::toHash( key, m_buffersize ) );
    m_buffer[ hash ].append( key, value );
    m_numItems++;
}

//-------------------------------------------------------------------------------------------------
template<class T, class U>
inline
bool THashMap<T, U>::remove( const T &key ) {

}
 
//-------------------------------------------------------------------------------------------------
template<class T, class U>
inline
bool THashMap<T, U>::hasKey( const T &key ) {
    const unsigned int hash( Hash::toHash( key, m_buffersize ) );
    const Node &node( m_buffer[ hash ] );
    if( node.m_key == key ) {
        return true;
    }

    if( nullptr != node.m_next ) {
        Node *next( node.m_next );
        while( next ) {
            if( next->m_key == key ) {
                return true;
            }
            next = next->m_next;
        }
    }

    return false;
}

//-------------------------------------------------------------------------------------------------
template<class T, class U>
inline
U &THashMap<T, U>::getValue( const T &key ) const {
    static U dummy;
    const unsigned int pos( Hash::toHash( key, m_buffersize ) );
    if( m_buffer[ pos ].m_key == key ) {
        Node &node( m_buffer[ pos ] );
        if( !node.m_next ) {
            return node.m_value;
        } else {
            Node *next( node.m_next );
            while( next->m_key != key ) {
                next = next->m_next;
                if( !next ) {
                    return dummy;
                }
            }
        }
    }

    return dummy;

}

//-------------------------------------------------------------------------------------------------
template<class T, class U>
inline
U &THashMap<T, U>::operator [] ( const T &key ) const {
    static U dummy;
    const unsigned int pos( Hash::toHash( key, m_buffersize ) );
    if( m_buffer[ pos ].m_hash == pos ) {
        if( !m_buffer[ pos ].node ) {
            return m_buffer[ pos ].m_value;
        } else {
            Node next( m_buffer[ pos ].m_next );
            while( next->m_hash != pos ) {
                next = next->m_next;
                if( !next ) {
                    return dummy;
                }
            }

            return next->m_value;
        }
    }
    return dummy;
}

//-------------------------------------------------------------------------------------------------
template<class T, class U>
inline
THashMap<T, U>::Node::Node()
: m_key( UnsetNode )
, m_value()
, m_next( nullptr ) {
    // empty
}

//-------------------------------------------------------------------------------------------------
template < class T, class U >
inline
THashMap<T, U>::Node::~Node() {

}

//-------------------------------------------------------------------------------------------------

} // Namespace CPPCore

#endif // CPPCORE_THASHMAP_H_INC
