/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2019 Kim Kulling

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

#include <stddef.h>
#include <cppcore/Common/CString.h>
#include <stdio.h>

namespace CPPCore {

//-------------------------------------------------------------------------------------------------
///	@class		TPoolAllocator
///	@ingroup	CPPCore
///
///	@brief  This class implements a simple poll-based allocation scheme.
/// Initially you have to define its size. Each allocation will be done from this initially created 
/// pool. You have to release all pooled instances after the usage. 
/// This allocation scheme is fast and does no call any new-calls during the lifetime of the 
/// allocator.
//-------------------------------------------------------------------------------------------------
template<class T>
class TPoolAllocator {
public:
    TPoolAllocator();
    TPoolAllocator(size_t numItems);
    ~TPoolAllocator();
    T *alloc();
    void release();
    void reserve(size_t size);
    void clear();
    size_t capacity() const;
    size_t reservedMem() const;
    size_t freeMem() const;
    void dumpAllocations(CString & allocs);
    void resize(size_t newSize);
    TPoolAllocator(const TPoolAllocator&) = delete;
    TPoolAllocator(TPoolAllocator&&) = delete;
    TPoolAllocator& operator = (const TPoolAllocator&) = delete;
    

private:
    struct Pool {
        size_t  m_poolsize;
        T*      m_pool;
        size_t  m_currentIdx;
        Pool   *m_next;

        Pool()
        : m_poolsize(0)
        , m_pool(nullptr)
        , m_currentIdx(0) 
        , m_next( nullptr ) {
            // empty
        }

        Pool(size_t numItems, Pool *prev )
        : m_poolsize( numItems )
        , m_pool(nullptr)
        , m_currentIdx(0)
        , m_next(prev) {
            m_pool = new T[m_poolsize];
        }
    };

    Pool *m_first;
    Pool *m_current;
    size_t  m_capacity;
};

template<class T>
inline
TPoolAllocator<T>::TPoolAllocator()
: m_first( nullptr )
, m_current( nullptr )
, m_capacity( 0L ) {
    // empty
}

template<class T>
inline
TPoolAllocator<T>::TPoolAllocator(size_t numItems)
: m_first( nullptr )
, m_current( nullptr ) {
    m_first = new Pool( numItems );
    m_current = m_first; 
}

template<class T>
inline
TPoolAllocator<T>::~TPoolAllocator() {
    clear();
}

template<class T>
inline
T *TPoolAllocator<T>::alloc() { 
    if (nullptr == m_current) {
        return nullptr;
    }

    if ( m_current->m_currentIdx == m_current->m_poolsize ) {
        resize(m_current->m_poolsize);
        m_current->m_next = new Pool(m_first->m_poolsize, m_current );
        return nullptr;
    }
    
    m_current->m_currentIdx++;
    return &m_current->m_pool[m_current->m_currentIdx-1];
}

template<class T>
inline
void TPoolAllocator<T>::release() {
    if (nullptr == m_current) {
        return;
    }

    m_current->m_currentIdx = 0;
}

template<class T>
inline
void TPoolAllocator<T>::reserve(size_t size) {
    clear();
    
    m_first = new Pool(size, nullptr );
    m_current = m_first;
    
    m_current->m_pool = new T[ size ];
    m_current->m_poolsize = size;
}

template<class T>
inline
void TPoolAllocator<T>::clear() {
    if (nullptr == m_current) {
        return;
    }

    delete [] m_current->m_pool;
    m_current->m_pool = nullptr;
    m_current->m_currentIdx = 0;
    m_current->m_poolsize = 0;
}

template<class T>
inline
size_t TPoolAllocator<T>::capacity() const {
    if (nullptr == m_current) {
        return 0L;
    }

    return m_current->m_poolsize;
}

template<class T>
inline
size_t TPoolAllocator<T>::reservedMem() const {
    return m_capacity;
}

template<class T>
inline
size_t TPoolAllocator<T>::freeMem() const {
    if (nullptr == m_current) {
        return 0L;
    }

    return (m_current->m_poolsize - m_current->m_currentIdx)-1;
}

template<class T>
inline
void TPoolAllocator<T>::dumpAllocations(CString & allocs) {
    allocs.clear();
    char buffer[512];
    sprintf(buffer, "Number allocations = %d\n", (int)m_current->m_currentIdx);
    allocs.set(buffer);
}

template<class T>
inline
void TPoolAllocator<T>::resize(size_t newSize) {
    if (newSize < m_current->m_poolsize) {
        return;
    }

    if (nullptr == m_first) {
        m_first = new Pool(newSize, nullptr);
        m_current = m_first;
        return;
    }

    m_current->m_next = new Pool(m_current->m_poolsize, m_current);
    m_current = m_current->m_next;
}

}
