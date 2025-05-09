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

#include <string.h>
#include <cassert>

namespace cppcore {

//-------------------------------------------------------------------------------------------------
/// @class    TArray
/// @ingroup  CPPCore
///
/// @brief This template class implements a simple array with dynamic boundaries.
///
/// You can use it to add new items, remove them and iterate through them. The data items are
/// stores in an array.
//-------------------------------------------------------------------------------------------------
template <class T, size_t len>
class TStaticArray {
public:
    /// @brief The default class constructor.
    TStaticArray();

    /// @brief  The class constructor with the initial value.
    /// @param[in] initValue    The initial value.
    explicit TStaticArray(T initValue);

    /// @brief The copy constructor.
    /// @param  rhs [in] The array to copy from.
    TStaticArray(const TStaticArray<T, len> &rhs);

    /// @brief  The class destructor.
    ~TStaticArray() = default;

    /// @brief  Returns the number of items in the array.
    /// @return  The size of the array.
    size_t size() const;

    /// @brief  Will set the item at the given index.
    /// @param[in] index  The requested index.
    /// @param[in] value  The new value.
    void set(size_t index, T value);

    /// @brief  Will set all values to the same value.
    /// @param[in] value   The value to set.
    void memset(T value);

    /// @brief  The index op.
    T operator[](size_t index) const;

    /// @brief  The index op.
    T &operator[](size_t index);
    bool operator==(const TStaticArray<T, len> &rhs) const;
    TStaticArray<T, len> &operator=(const TStaticArray<T, len> &rhs);

private:
    T mArray[len];
    size_t mLen;
};

template <class T, size_t len>
inline TStaticArray<T, len>::TStaticArray() :
        mLen(len) {
    // empty
}

template <class T, size_t len>
inline TStaticArray<T, len>::TStaticArray(T initValue) :
        mLen(len) {
    memset(initValue);
}

template <class T, size_t len>
inline TStaticArray<T, len>::TStaticArray(const TStaticArray<T, len> &rhs) :
        mLen(rhs.mLen) {
    for (size_t i = 0; i < mLen; ++i) {
        mArray[i] = rhs.mArray[i];
    }
}

template <class T, size_t len>
inline void TStaticArray<T, len>::set(size_t index, T value) {
    assert(index < mLen);

    mArray[index] = value;
}

template <class T, size_t len>
inline void TStaticArray<T, len>::memset(T value) {
    for (size_t i = 0; i < mLen; ++i) {
        mArray[i] = value;
    }
}

template <class T, size_t len>
inline size_t TStaticArray<T, len>::size() const {
    return mLen;
}

template <class T, size_t len>
inline T TStaticArray<T, len>::operator[](size_t index) const {
    assert(index < mLen);

    return mArray[index];
}

template <class T, size_t len>
inline T &TStaticArray<T, len>::operator[](size_t index) {
    return mArray[index];
}

template <class T, size_t len>
inline bool TStaticArray<T, len>::operator==(const TStaticArray<T, len> &rhs) const {
    for (size_t i = 0; i < mLen; ++i) {
        if (mArray[i] != rhs.mArray[i]) {
            return false;
        }
    }

    return true;
}

template <class T, size_t len>
inline TStaticArray<T, len> &TStaticArray<T, len>::operator = (const TStaticArray<T, len> &rhs) {
    if (*this == rhs) {
        return *this;
    }

    for (unsigned int i = 0; i < mLen; ++i) {
       mArray[i] = rhs.mArray[i];
    }

    return *this;
}

} // namespace cppcore
