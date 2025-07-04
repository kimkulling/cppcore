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

namespace cppcore {

//-------------------------------------------------------------------------------------------------
///	@class		TStringView
///	@ingroup	CPPCore
///
/// @brief  
//-------------------------------------------------------------------------------------------------
template <class T>
class TStringView {
public:
    using const_iterator = const T*;

    /// @brief The default constructor.
    TStringView() = default;

    /// @brief The constructor with the buffer.
    /// @param ptr      Pointer to the buffer
    /// @param len      The buffer size
    TStringView(const T *ptr, size_t len);
    
    /// @brief The class destructor.
    ~TStringView() = default;

    /// @brief Will return the size of the view.
    /// @return The size of the view
    size_t size() const;

    /// @brief Will return the data with an offset, if given.
    /// @param offset   The offset in the view.
    /// @return Pointer to the data
    const T *data(size_t offset = 0) const;

    /// @brief Will return true, if there is no string to view.
    /// @return true for empty
    bool isEmpty() const;

    /// @brief Will return the first entry.
    /// @return The first entry
    const_iterator begin() const;

    /// @brief Will return the end entry.
    /// @return The end entry
    const_iterator end() const;

private:
    const T *mPtr = nullptr;
    size_t mLen = 0;
};

template <class T>
inline TStringView<T>::TStringView(const T *ptr, size_t len) :
        mPtr(ptr), mLen(len) {
    // empty
}

template <class T>
inline size_t TStringView<T>::size() const {
    return mLen;
}

template <class T>
inline const T *TStringView<T>::data(size_t offset) const {
    if (offset > mLen) {
        return nullptr;
    }
    return mPtr + offset;
}

template <class T>
inline bool TStringView<T>::isEmpty() const {
    return mLen == 0;
}

template <class T>
inline typename TStringView<T>::const_iterator TStringView<T>::begin() const {
    if (isEmpty()) {
        return end();
    }
    return mPtr;
}

template <class T>
inline typename TStringView<T>::const_iterator TStringView<T>::end() const {
    return mPtr + mLen;
}

} // namespace cppcore
