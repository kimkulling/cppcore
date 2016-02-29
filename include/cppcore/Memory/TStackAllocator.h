/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2016 Kim Kulling

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
#pragma once

namespace CPPCore {

template<class T>
class TStackAllocator {
public:
    TStackAllocator( size_t initSize );
    ~TStackAllocator();
    T *alloc( size_t size );
    void release( T *ptr );
    void reserve( size_t size );
    void clear();
    size_t capacity() const;
    size_t reservedMem() const;
    size_t freeMem() const;

private:
    struct Header {
        size_t m_size;
    };
    size_t m_capacity;
    size_t m_top;
    T *m_data;

private:
};

template<class T>
inline
TStackAllocator<T>::TStackAllocator( size_t initSize )
: m_capacity( 0 )
, m_top( 0 )
, m_data( nullptr ) {
    reserve( initSize );
}

template<class T>
inline
TStackAllocator<T>::~TStackAllocator() {
    clear();
}

template<class T>
inline
T *TStackAllocator<T>::alloc( size_t size ) {
    if ( 0 == size ) {
        return nullptr;
    }

    size_t newSize( size * sizeof( T ) + sizeof( Header ) );
    const size_t limit( m_top + newSize );
    if ( limit > m_capacity ) {
        return nullptr;
    }

    T *ptr = ( &m_data[ m_top ] ) + sizeof( Header );
    Header *header = ( Header* ) ( &m_data[ m_top ] );
    header->m_size = size;
    m_top += newSize;

    return ptr;
}

template<class T>
inline
void TStackAllocator<T>::release( T *ptr ) {
    if ( nullptr == ptr ) {
        return;
    }

    Header *head = ( Header* ) ptr - sizeof( Header );
    const size_t allocSize = ( head->m_size * sizeof( T ) ) - sizeof( Header );
    m_top -= allocSize;
}

template<class T>
inline
void TStackAllocator<T>::reserve( size_t size ) {
    if ( size > ( m_capacity/sizeof( T )  ) ) {
        clear();
        m_capacity = size * sizeof( T );
        m_data = new T[ m_capacity ];
    }
}

template<class T>
inline
void TStackAllocator<T>::clear() {
    delete [] m_data;
    m_data = nullptr;
    m_capacity = 0;
    m_top = 0;
}

template<class T>
inline
size_t TStackAllocator<T>::capacity() const {
    return m_capacity;
}

template<class T>
inline
size_t TStackAllocator<T>::reservedMem() const {
    return m_top;
}

template<class T>
inline
size_t TStackAllocator<T>::freeMem() const {
    return ( m_capacity - m_top );
}

} // Namespace CPPCore
