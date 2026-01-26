/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2025 Kim Kulling

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
///	@class		TPoolAllocator
///	@ingroup	CPPCore
///
///	@brief  This class implements a simple pool-based allocation scheme.
/// Initially you have to define its size. Each allocation will be done from this initially created
/// pool. You have to release all pooled instances after the usage.
/// This allocation scheme is fast and does no call any new-calls during the lifetime of the
/// allocator.
/// @code
/// struct foo { int payload[10]; };
/// TPoolAllocator<foo> allocator(10000);
/// foo *instance = allocator.alloc();
/// ...
/// allocator.release(instance);
/// @endcode
//-------------------------------------------------------------------------------------------------
template <class T>
class TPoolAllocator {
public:
    /// @brief  The default class constructor.
    TPoolAllocator() = default;

    /// @brief  The class constructor with the pool size.
    /// @param  numItems    [in] The pool size.
    TPoolAllocator(size_t numItems);

    /// @brief  The class destructor.
    ~TPoolAllocator();

    /// @brief  WIll alloc one item from the pool.
    /// @return The pointer to the allocated item.
    T *alloc();

    /// @brief  Will release all allocated items.
    void release();

    /// @brief  Will reserve the pool.
    /// @apram  size    [in] The pool size to reserve.
    void reserve(size_t size);

    /// @brief  Will clear the pool, memory will be deallocated.
    /// @note   All instances which are currently is use will get invalid. PLease use with care.
    void clear();

    /// @brief  Returns the capacity of items in the pool allocator.
    /// @return The capacity.
    size_t capacity() const;

    /// @brief  WIll return the reserved memory in bytes.
    /// @return The reserved memory in bytes.
    size_t reservedMem() const;

    /// @brief  Will return the free memory in the pool in bytes.
    /// @return The free memory in bytes.
    size_t freeMem() const;

    /// @brief  Will dump a statistic overview into the given string.
    /// @param  allocs  [inout] The string to hold the allocation statistic.
    void dumpAllocations(std::string &allocs);

    /// @brief  Will perform a resize for the pool.
    /// @param  growSize    [in] The soze to grow.
    void resize(size_t growSize);

    /// @brief  Will reset the allocator.
    void reset();

    /// No copying allowed
    CPPCORE_NONE_COPYING(TPoolAllocator)

private:
    struct Pool {
        size_t mPoolsize{0u};
        T *mPool{nullptr};
        size_t mCurrentIdx{0u};
        Pool *mNext{nullptr};

        Pool() = default;
        
        Pool(size_t numItems, Pool *prev) :
                mPoolsize(numItems),
                mNext(prev) {
            mPool = new T[mPoolsize];
        }

        ~Pool() {
            delete[] mPool;
        }

        CPPCORE_NONE_COPYING(Pool)
    };

    Pool *getFreePool() {
        Pool *current = mFreeList;
        if (nullptr != mFreeList) {
            mFreeList = mFreeList->mNext;
        }
        return current;
    }

    Pool *mFirst{nullptr};
    Pool *mCurrent{nullptr};
    Pool *mFreeList{nullptr};
    size_t mCapacity{0L};
};

template <class T>
inline TPoolAllocator<T>::TPoolAllocator(size_t numItems) {
    mFirst = new Pool(numItems, nullptr);
    mCapacity += numItems;
    mCurrent = mFirst;
}

template <class T>
inline TPoolAllocator<T>::~TPoolAllocator() {
    clear();
}

template <class T>
inline T *TPoolAllocator<T>::alloc() {
    if (nullptr == mCurrent) {
        return nullptr;
    }

    if (mCurrent->mCurrentIdx == mCurrent->mPoolsize) {
        resize(mCurrent->mPoolsize);
    }

    T *ptr = &mCurrent->mPool[mCurrent->mCurrentIdx];
    mCurrent->mCurrentIdx++;

    return ptr;
}

template <class T>
inline void TPoolAllocator<T>::release() {
    if (nullptr == mCurrent) {
        return;
    }

    Pool *current = mFirst;
    while (nullptr != current) {
        current->mCurrentIdx = 0;
        current = current->mNext;
    }
    mFreeList = mFirst->mNext;
    mCurrent = mFirst;
}

template <class T>
inline void TPoolAllocator<T>::reserve(size_t size) {
    clear();

    mFirst = new Pool(size, nullptr);
    mCurrent = mFirst;

    mCurrent->mPool = new T[size];
    mCurrent->mPoolsize = size;

    mCapacity = size;
}

template <class T>
inline void TPoolAllocator<T>::clear() {
    if (nullptr == mCurrent) {
        return;
    }

    Pool *next = mFirst;
    while (nullptr != next) {
        Pool *current = next;
        next = current->mNext;
        delete current;
    }
    mCurrent = nullptr;
    mFreeList = nullptr;
}

template <class T>
inline size_t TPoolAllocator<T>::capacity() const {
    return mCapacity;
}

template <class T>
inline size_t TPoolAllocator<T>::reservedMem() const {
    return mCapacity * sizeof(T);
}

template <class T>
inline size_t TPoolAllocator<T>::freeMem() const {
    if (nullptr == mCurrent) {
        return 0L;
    }

    return (mCurrent->mPoolsize - mCurrent->mCurrentIdx);
}

template <class T>
inline void TPoolAllocator<T>::dumpAllocations(std::string &allocs) {
    allocs.clear();
    allocs += "Number allocations = ";
    allocs += std::to_string(mCurrent->mCurrentIdx);
    allocs += "\n";
}

template <class T>
inline void TPoolAllocator<T>::resize(size_t growSize) {
    if (nullptr != mCurrent) {
        if (growSize < mCurrent->mPoolsize) {
            return;
        }
    }

    if (nullptr == mFirst) {
        mFirst = new Pool(growSize, nullptr);
        mCurrent = mFirst;
        mCapacity += mCurrent->mPoolsize;
    } else {
        Pool *pool = getFreePool();
        if (nullptr == pool) {
            pool = new Pool(growSize, nullptr);
            mCapacity += growSize;
        }
        mCurrent->mNext = pool;
        mCurrent = mCurrent->mNext;
    }
}

template<class T>
void TPoolAllocator<T>::reset() {
    mCurrent = mFirst;
}

} // namespace cppcore
