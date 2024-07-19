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
#pragma once

#include <cppcore/CPPCoreCommon.h>

#include <string>

namespace cppcore {

//-------------------------------------------------------------------------------------------------
///	@class		TStackAllocator
///	@ingroup	CPPCore
///
///	@brief  This class implements a simple stack-based allocation scheme.
/// Initially you have to define its size. Each allocation will be done from this initially created
/// pool and must be deallocated in LIFO order. All data will be released when the allocator will
/// be released.
/// This allocation scheme is fast and does no call any new-calls during the lifetime of the
/// allocator pool.
//-------------------------------------------------------------------------------------------------
template <class T>
class TStackAllocator {
public:
    /// @brief  The default class constructor.
    TStackAllocator();

    /// @brief  The class constructor with the initial size for the stack.
    /// @param  initSize    [in] The initial size.
    TStackAllocator(size_t initSize);

    /// @brief  The class destructor.
    ~TStackAllocator();

    /// Will alloc the number of items from the stack.
    /// @param  size    [in] The requested size of items.
    T *alloc(size_t size);

    /// @brief  Will release the last item from the stack. A basic check will be performed to
    ///         ensure that it is the correct item.
    /// @param  ptr     [in] The pointer to validate.
    bool release(T *ptr);

    /// @brief
    void reserve(size_t size);

    /// @brief  Will clear the whole memory, all used data will be marked as invalid.
    void clear();

    /// @brief  Will reset the allocated memory, all used data will be marked as invalid.
    void reset();

    /// @brief  Returns the number of allocated instances on the stack
    /// @return The number of allocated instance.
    size_t capacity() const;

    /// @brief  Returns the allocated memory in bytes.
    /// @return The allocated memory in bytes.
    size_t reservedMem() const;

    /// @brief  Returns the free memory in bytes.
    /// @return The free memory in bytes.
    size_t freeMem() const;

    /// @brief  Will dump a statistic overview into the given string.
    /// @param  allocs  [inout] The string to hold the allocation statistic.
    void dumpAllocations(std::string &allocs);

    // To copying allowed
    CPPCORE_NONE_COPYING(TStackAllocator)

private:
    using byte_t = unsigned char;

    struct Header {
        size_t m_size;
    };
    size_t m_capacity;
    size_t m_top;
    size_t m_numAllocs;
    byte_t *m_data;
};

template <class T>
inline TStackAllocator<T>::TStackAllocator() :
        m_capacity(0),
        m_top(0),
        m_numAllocs(0),
        m_data(nullptr) {
    // empty
}

template <class T>
inline TStackAllocator<T>::TStackAllocator(size_t initSize) :
        m_capacity(0),
        m_top(0),
        m_numAllocs(0),
        m_data(nullptr) {
    reserve(initSize);
}

template <class T>
inline TStackAllocator<T>::~TStackAllocator() {
    clear();
}

template <class T>
inline T *TStackAllocator<T>::alloc(size_t size) {
    if (0 == size) {
        return nullptr;
    }

    const size_t range(size * sizeof(T) + sizeof(Header));
    const size_t limit(m_top + range);
    if (limit > m_capacity) {
        return nullptr;
    }

    // head
    Header *header = (Header *)(&m_data[m_top]);
    header->m_size = size * sizeof(T);
    m_top += sizeof(Header);

    // data
    T *ptr = (T *)(&m_data[m_top]);
    m_top += header->m_size;
    m_numAllocs++;

    return ptr;
}

template <class T>
inline bool TStackAllocator<T>::release(T *ptr) {
    if (nullptr == ptr) {
        return false;
    }

    // head
    byte_t *tmp = (byte_t *)ptr;
    tmp = tmp - sizeof(Header);
    Header *head = (Header *)tmp;
    const size_t allocSize = head->m_size;

    // data
    m_top -= allocSize;
    m_top -= sizeof(Header);
    m_numAllocs--;

    return true;
}

template <class T>
inline void TStackAllocator<T>::reserve(size_t size) {
    if (size > (m_capacity)) {
        clear();
        m_capacity = size * sizeof(T);
        m_data = new byte_t[m_capacity];
    }
}

template <class T>
inline void TStackAllocator<T>::clear() {
    delete[] m_data;
    m_data = nullptr;
    m_capacity = 0;
    m_top = 0;
}
    
template <class T>
inline void TStackAllocator<T>::reset() {
    m_top = 0;
}

template <class T>
inline size_t TStackAllocator<T>::capacity() const {
    return m_capacity;
}

template <class T>
inline size_t TStackAllocator<T>::reservedMem() const {
    return m_top;
}

template <class T>
inline size_t TStackAllocator<T>::freeMem() const {
    return (m_capacity - m_top);
}

template <class T>
inline void TStackAllocator<T>::dumpAllocations(std::string &allocs) {
    allocs.clear();
    allocs += "Number allocations = ";
    allocs += std::to_string(m_numAllocs);
    allocs += "\n";
}

} // Namespace cppcorecppcore
