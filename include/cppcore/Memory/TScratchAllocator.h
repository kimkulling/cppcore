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
#include <memory>
#include <limits>

namespace cppcore {

//-------------------------------------------------------------------------------------------------
/// @class      TScratchAllocator
/// @ingroup    CPPCore
///
/// @brief A simple scratch allocator.
///
/// You can use it to manage all the dynamic allocations without caring about cleaning it up. All
/// Allocations will be a one-shot alloc, which do not need to get released. When calling clear
/// all allocation will be invalidated and cannot be used anymore.
//-------------------------------------------------------------------------------------------------
template<class T>
class TScratchAllocator {
public:
    /// @brief  The default class constructor.
    TScratchAllocator();
    
    /// @brief The move constructor
    /// @param other Will be moved to
    TScratchAllocator(TScratchAllocator&& other) noexcept;

    /// @brief The move operator
    /// @param other Will be moved to
    /// @return instance to moved to.
    TScratchAllocator& operator = (TScratchAllocator&& other) noexcept

    /// @brief  The class constructor with the pool size.
    /// @param[in]  numItems    The buffer size.
    explicit TScratchAllocator(size_t numItems);

    /// @brief  The class destructor.
    ~TScratchAllocator();

    /// @brief  Will allocate the number of items.
    /// @param[in] numItems    The number of items.
    /// @return Pointr showing to the scratch buffer.
    T *alloc(size_t numItems);

    /// @brief  Will reserve the pool.
    /// @apram[in] size    The pool size to reserve.
    void reserve(size_t size);

    /// @brief  Will clear the pool, memory will be deallocated.
    /// @note   All instances which are currently is use will get invalid. PLease use with care.
    void clear();

    /// @brief  Returns the capacity of items in the pool allocator.
    /// @return The capacity.
    size_t capacity() const;

    /// @brief  Will return the reserved memory in bytes.
    /// @return The reserved memory in bytes.
    size_t reservedMem() const;

    /// @brief  Will return the free memory in the pool in bytes.
    /// @return The free memory in bytes.
    size_t freeMem() const;

    /// No copying allowed
    CPPCORE_NONE_COPYING(TScratchAllocator)

private:
    T *mBlock;
    size_t mSize;
    size_t mIndex;
};

template<class T>
inline TScratchAllocator<T>::TScratchAllocator() :
        mBlock(nullptr), mSize(0u), mIndex(0u) {
    // empty
}

template<class T>
inline TScratchAllocator<T>::TScratchAllocator(size_t numItems) :
        mBlock(nullptr), mSize(numItems), mIndex(0u) {
    reserve(numItems);
}

template<class T>
inline TScratchAllocator<T>::~TScratchAllocator() {
    clear();
}

template<class T>
inline T *TScratchAllocator<T>::alloc(size_t numItems) {
    if (numItems == 0) {
        return nullptr;
    }

    // Check for overflow
    if (numItems > std::numeric_limits<size_t>::max() / sizeof(T)) {
        return nullptr;
    }

     if ((mIndex + numItems) > mSize) {
         return nullptr;
     }
 
    // Ensure alignment
    size_t alignment = alignof(T);
    mIndex = (mIndex + alignment - 1) & ~(alignment - 1);

    T *ptr = &mBlock[mIndex];
    mIndex += numItems;
    return ptr;
}

template<class T>
void TScratchAllocator<T>::reserve(size_t size) {
    clear();
    mBlock = new T[size];
    mSize = size;
    mIndex = 0u;
}

template<class T>
inline void TScratchAllocator<T>::clear() {
    delete [] mBlock;
    mBlock = nullptr;
    mSize = 0u;
}

template<class T>
inline size_t TScratchAllocator<T>::capacity() const {
    return mSize;
}

template<class T>
inline size_t TScratchAllocator<T>::reservedMem() const {
    return mIndex;
}

template<class T>
inline size_t TScratchAllocator<T>::freeMem() const {
    return (mSize - mIndex);
}

template<class T>
inline TScratchAllocator(TScratchAllocator&& other) noexcept :
    mBlock(other.mBlock),
    mSize(other.mSize),
    mIndex(other.mIndex) {
    other.mBlock = nullptr;
    other.mSize = 0;
    other.mIndex = 0;
}

template<class T>
inline TScratchAllocator& operator=(TScratchAllocator&& other) noexcept {
    if (this != &other) {
        clear();
        mBlock = other.mBlock;
        mSize = other.mSize;
        mIndex = other.mIndex;
        other.mBlock = nullptr;
        other.mSize = 0;
        other.mIndex = 0;
    }
    return *this;
}
using ScratchAllocator = TScratchAllocator<char>;

} // namespace cppcore
