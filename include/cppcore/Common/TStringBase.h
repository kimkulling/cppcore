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

#include "string.h"
#include <cppcore/Common/Hash.h>
#include <cppcore/CPPCoreCommon.h>

namespace cppcore {

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
    TStringBase() noexcept = default;

    /// @brief  The class constructor with a pointer showing to the data buffer.
    /// @param  pPtr        [in] The data buffer.
    TStringBase(const T *pPtr, size_t size);

    /// @brief  The class destructor.
    ~TStringBase();

    void set(const T *ptr, size_t size);
    void clear();
    void reset();
    size_t size() const;
    size_t capacity() const;
    const T *c_str() const;

    /// @brief  Helper method to copy data into the string.
    /// @param  base        [inout] The string data to copy in.
    /// @param  pPtr        [in] The data source.
    static void copyFrom(TStringBase<T> &base, const T *pPtr, size_t size);
     
    bool operator == (const TStringBase<T> &rhs) const;
    bool operator != (const TStringBase<T> &rhs) const;

private:
    static constexpr size_t InitSize = 256;
    T mBuffer[InitSize] = {};
    T *mStringBuffer{nullptr};
    size_t mSize{0};
    size_t mCapacity{256};
    HashId mHashId{0};
};

template <class T>
inline TStringBase<T>::TStringBase(const T *pPtr, size_t size) {
    copyFrom(*this, pPtr, size);
    mHashId = THash<HashId>::toHash(pPtr, mSize);
}

template <class T>
inline TStringBase<T>::~TStringBase() {
    clear();
}

template <class T>
inline void TStringBase<T>::set(const T *ptr, size_t size) {
    reset();
    if (nullptr != ptr) {
        copyFrom(*this, ptr, size);
    }
}

template <class T>
inline void TStringBase<T>::reset() {
    mSize = 0u;
    mHashId = 0;
}

template <class T>
inline size_t TStringBase<T>::size() const {
    return mSize;
}

template <class T>
inline size_t TStringBase<T>::capacity() const {
    return mCapacity;
}

template <class T>
inline const T *TStringBase<T>::c_str() const {
    if (mStringBuffer != nullptr) {
        return mStringBuffer;
    }

    return mBuffer;
}

template <class T>
inline void TStringBase<T>::clear() {
    if (mStringBuffer != nullptr) {
        delete [] mStringBuffer;
        mStringBuffer = nullptr;
        mCapacity = InitSize;
    }
    reset();
}

template <class T>
inline void TStringBase<T>::copyFrom(TStringBase<T> &base, const T *ptr, size_t size) {
    if (ptr != nullptr) {
        T *targetPtr = base.mBuffer;
        
        if (size > 0) {
            if (size > base.mCapacity) {
                base.mStringBuffer = new T[size];
                base.mCapacity = size;
                targetPtr = base.mStringBuffer;
            }
            memcpy(targetPtr, ptr, size);
            base.mSize = size;
        }
    }
}

template <class T>
inline bool TStringBase<T>::operator == (const TStringBase<T> &rhs) const {
    if (rhs.mSize != mSize) {
        return false;
    }

    if (mHashId != rhs.mHashId) {
        return false;
    }
    
    // Fallback to actual comparison in case of hash collision
    return memcmp(c_str(), rhs.c_str(), mSize * sizeof(T)) == 0;
}

template <class T>
inline  bool TStringBase<T>::operator != (const TStringBase<T> &rhs) const {
    return !(*this == rhs);
}

} // namespace cppcore
