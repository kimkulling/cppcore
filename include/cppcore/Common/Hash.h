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

#include <cppcore/CPPCoreCommon.h>

namespace cppcore {

//-------------------------------------------------------------------------------------------------
///	@class		THash
///	@ingroup	CPPCore
///
///	@brief  This class is used to calculate the hash value for a given integer or character buffer.
//-------------------------------------------------------------------------------------------------
template<class T>
class THash {
public:
    /// @brief  The default class constructor.
    THash() = default;

    /// @brief  The class constructor with a given hash value.
    /// @param  hash    [in] An integer value to compute the hash from.
    explicit THash(T hash);

    /// @brief  The class constructor with a given char buffer.
    /// @param  value   [in] A character buffer to compute the hash from.
    /// @param  base    [in] The table base.
    explicit THash(const char *buffer, T base);

    /// @brief  The class constructor with a given unsigned int value.
    /// @param  value   [in] An unsigned int value to compute the hash from.
    /// @param  base    [in] The table base.
    explicit THash(T value, T base);

    /// @brief  The class destructor.
    ~THash() = default;

    /// @brief  Computes the hash value for a given character buffer.
    /// @param  buffer  [in] The buffer.
    /// @param  base    [in] The table base.
    /// @return The hash value.
    static T toHash(const char *buffer, T base);

    /// @brief  Computes the hash value for a given unsigned int value.
    /// @param  buffer  [in] The unsigned int value.
    /// @param  base    [in] The table base.
    /// @return The hash value.
    static T toHash(T value, T base);

    /// brief    Returns the stored hash value.
    /// @return The hash value.
    T hashValue() const;

private:
    T mHash{0};
};

template <class T>
inline THash<T>::THash(T hash) : mHash(hash) {
    // empty
}

template <class T>
inline THash<T>::THash(const char *buffer, T base) : mHash(THash::toHash(buffer, base)) {
    // empty
}

template <class T>
inline THash<T>::THash(T value, T base) : mHash(THash::toHash(value, base)) {
    // empty
}

template <class T>
inline T THash<T>::toHash(const char *buffer, T base) {
    T hash = 0;
    if (nullptr == buffer) {
        return hash;
    }

    // using division-rest method
    // see http://de.wikipedia.org/wiki/Divisionsrestmethode
    for (size_t i = 0; i < strlen(buffer); ++i) {
        hash = (hash * 128 + buffer[i]) % base;
    }

    return hash;
}

template <class T>
inline T THash<T>::toHash(T value, T base) {
    const T hash = value % base;
    return hash;
}

template <class T>
inline T THash<T>::hashValue() const {
    return mHash;
}

} // Namespace cppcore
