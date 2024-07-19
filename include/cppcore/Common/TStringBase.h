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

#include "string.h"
#include <cppcore/CPPCoreCommon.h>
#include <malloc.h>

namespace cppcore {

template <class T>
struct Allocator {
    inline T *alloc(size_t size, size_t alignment) {
        return (T*) _aligned_malloc(size, alignment);
    }

    inline void dealloc(T *ptr) {
        _aligned_free(ptr);
    }

    inline static size_t countChars(const T *ptr) {
        if (nullptr != ptr) {
            return 0;
        }

        return (::strlen(ptr));
    }
};

//-------------------------------------------------------------------------------------------------
///	@class		TStringBase
///	@ingroup    CPPCore
///
///	@brief  This class is used to describe the inner data of a string.
//-------------------------------------------------------------------------------------------------
template <class T>
class TStringBase {
public:
    /// @brief  The default class constructor.
    TStringBase() noexcept;

    /// @brief  The class constructor with a pointer showing to the data buffer.
    /// @param  pPtr        [in] The data buffer.
    TStringBase(const T *pPtr);

    /// @brief  The class destructor.
    ~TStringBase();

    void set(const T *ptr);

    /// @brief  Helper method to copy data into the string.
    /// @param  base        [inout] The string data to copy in.
    /// @param  pPtr        [in] The data source.
    static void copyFrom(TStringBase<T> &base, const T *pPtr);
     
    bool operator == (const TStringBase<T> &rhs) const;
    bool operator != (const TStringBase<T> &rhs) const;

    T *m_pStringBuffer;
    size_t m_size;
    size_t m_capacity;
    Allocator<T> mAllocator;
};

template <class T>
inline TStringBase<T>::TStringBase() noexcept :
        m_pStringBuffer(nullptr),
        m_size(0),
        m_capacity(0),
        mAllocator() {
    // empty
}

template <class T>
inline TStringBase<T>::TStringBase(const T *pPtr) :
        m_pStringBuffer(nullptr),
        m_size(0),
        m_capacity(0),
        mAllocator() {
    copyFrom(*this, pPtr);
}

template <class T>
inline TStringBase<T>::~TStringBase() {
    if (m_pStringBuffer) {
        mAllocator.dealloc(m_pStringBuffer);
        m_pStringBuffer = nullptr;
    }
}

template <class T>
inline void TStringBase<T>::set(const T *ptr) {
    mAllocator.dealloc(m_pStringBuffer);
    if (nullptr != ptr) {
        copyFrom(*this, ptr);
    }
}

template <class T>
inline void TStringBase<T>::copyFrom(TStringBase<T> &base, const T *ptr) {
    if (nullptr != ptr) {
        base.m_size = Allocator<T>::countChars(ptr);
        if (base.m_size) {
            base.m_capacity = base.m_size + 1;
            base.m_pStringBuffer = base.mAllocator.alloc(base.m_capacity, 16);
#ifdef CPPCORE_WINDOWS
            ::strncpy_s(base.m_pStringBuffer, base.m_capacity, ptr, base.m_size);
#else
            ::strncpy(base.m_pStringBuffer, ptr, base.m_size);
#endif
            base.m_pStringBuffer[base.m_size] = '\0';
        }
    }
}

template <class T>
inline bool TStringBase<T>::operator==( const TStringBase<T> &rhs ) const {
    if (rhs.m_size != m_size) {
        return false;
    }

    for (size_t i = 0; i < m_size; ++i) {
        if (rhs.m_pStringBuffer[i] != m_pStringBuffer[i]) {
            return false;
        }
    }

    return true;
}

template <class T>
inline  bool TStringBase<T>::operator!=(const TStringBase<T> &rhs) const {
    return !(*this == rhs);
}

    template <class TCharType>
class TStringView {
public:
    TStringView(TCharType *ptr);
    ~TStringView();
    size_t size() const;
    TCharType *data() const;

private:
    TCharType *mPtr;
    size_t mLen;
};

template <class TCharType>
inline TStringView<TCharType>::TStringView(TCharType *ptr) :
        mPtr(ptr),
        mLen(0) {
    if (nullptr != mPtr) {
        mLen = strlen(ptr);
    }
}

template <class TCharType>
inline TStringView<TCharType>::~TStringView() {
    // empty
}

template <class TCharType>
inline size_t TStringView<TCharType>::size() const {
    return mLen;
}

template <class TCharType>
inline TCharType *TStringView<TCharType>::data() const {
}

