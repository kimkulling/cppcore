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

#include <stddef.h>
#include <cppcore/Common/CString.h>
#include <stdio.h>

namespace CPPCore {

template<class T>
class TPoolAllocator {
public:
    TPoolAllocator();
    TPoolAllocator(size_t numItems);
    ~TPoolAllocator();
    T *alloc();
    void release(T *item);
    void reserve(size_t size);
    void clear();
    size_t capacity() const;
    size_t reservedMem() const;
    size_t freeMem() const;
    void dumpAllocations(CString & allocs);

private:
    size_t m_poolsize;
    T *m_pool;
    ui32 m_currentIdx;
    struct FreeItem {
        ui32 m_idx;
        FreeItem *m_next;
    };
    FreeItem *m_start;
};

template<class T>
inline
TPoolAllocator<T>::TPoolAllocator()
: m_poolsize(0)
, m_pool(nullptr)
, m_start( nullptr ) {
    // empty
}

template<class T>
inline
TPoolAllocator<T>::TPoolAllocator(size_t numItems)
: m_poolsize(numItems)
, m_pool(nullptr)
, m_currentIdx( 0 )
, m_start( nullptr ) {
    m_pool = new T[m_poolsize];
}

template<class T>
inline
TPoolAllocator<T>::~TPoolAllocator() {
    clear();
}

template<class T>
inline
T *TPoolAllocator<T>::alloc() {
    if ( m_currentIdx == m_poolsize ) {
        return nullptr;
    }
    
    ++m_currentIdx;
    return &m_pool[m_currentIdx-1];
}

template<class T>
inline
void TPoolAllocator<T>::release(T *item) {
    if (nullptr == item) {
        return;
    }

}

template<class T>
inline
void TPoolAllocator<T>::reserve(size_t size) {
    clear();
    m_pool = new T[ size ];
    m_poolsize = size;
}

template<class T>
inline
void TPoolAllocator<T>::clear() {
    if (nullptr == m_pool) {
        return;
    }

    delete [] m_pool;
    m_poolsize = 0;
    m_currentIdx = 0;
}

template<class T>
inline
size_t TPoolAllocator<T>::capacity() const {
    return m_poolsize;
}

template<class T>
inline
size_t TPoolAllocator<T>::reservedMem() const {
    return m_poolsize * sizeof(T);
}

template<class T>
inline
size_t TPoolAllocator<T>::freeMem() const {
    return m_poolsize - m_currentIdx;
}

template<class T>
inline
void TPoolAllocator<T>::dumpAllocations(CString & allocs) {
    const ui32 end(m_currentIdx - 1);
    for ()
}

}
