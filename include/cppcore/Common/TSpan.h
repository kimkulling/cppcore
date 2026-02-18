/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2026 Kim Kulling

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
#ifndef CPPCORE_COMMON_TSPAN_H
#define CPPCORE_COMMON_TSPAN_H

#include <cppcore/CPPCoreCommon.h>

namespace cppcore {

//-------------------------------------------------------------------------------------------------
///	@class		TSpan
///	@ingroup	CPPCore
///
///	@brief  This class implements a view onto array data.
//-------------------------------------------------------------------------------------------------
template<class T>
class TSpan {
public:
    /// @brief The default class constructor.
    TSpan() = default;

    /// @brief The class constructor with the pointer and the size of the array.
    /// @param[in] ptr  The pointer to the array.
    /// @param[in] size The array size.
    TSpan(const T *ptr, size_t size);

    /// @brief The class destructor.
    ~TSpan() = default;

    /// @brief Will return the data pointer showing to the first entry.
    /// @return The array pointer or nullptr, if no array was set.
    T* data() const;

    /// @brief Will return the number of items in the view.
    /// @return The number of items.
    size_t size() const;

    /// @brief Will return true, if the span view is empty.
    /// @return true, 
    bool empty() const;
    T operator[] (size_t index);
    const T operator[](size_t index) const;

private:
    const T *mData{nullptr};
    size_t mSize{0u};
};

template<class T>
inline TSpan<T>::TSpan(const T *ptr, size_t size) : mData(ptr), mSize(size) {
    // empty
}

template<class T>
inline T *TSpan<T>::data() const {
    return mData; 
}

template<class T>
inline size_t TSpan<T>::size() const { 
    return mSize; 
}

template<class T>
inline bool TSpan<T>::empty() const { 
    return mSize == 0; 
}

template<class T>
inline T TSpan<T>::operator[](size_t index) {
    if (index >= mSize) {
        return std::numeric_limits<T>::max();
    }
    return mData[index];
}

template<class T>
inline const T TSpan<T>::operator[](size_t index) const {
    return mData[index]; 
}

} // namespace cppcore

#endif // CPPCORE_COMMON_TSPAN_H