/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2018 Kim Kulling

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

namespace CPPCore {

//-------------------------------------------------------------------------------------------------
///	@class		TArray
///	@ingroup	CPPCore
///
///	@brief	This template class implements a simple array with dynamic boundaries. 
/// You can use it to add new items, remove them and iterate through them. The data items are 
/// stores in an array.
//-------------------------------------------------------------------------------------------------
template<class T, unsigned int len>
class TStaticArray {
public:
    TStaticArray();
    TStaticArray(const TStaticArray<T, len> &rhs);
    ~TStaticArray();
    void clear();
    unsigned int size() const;
    void set(unsigned int index, T value);
    T operator[](unsigned int index) const;
    T &operator[](unsigned int index);
    bool operator == (const TStaticArray<T, len> &rhs) const;
    TStaticArray<T, len> &operator = (const TStaticArray<T, len> &rhs);

private:
    T m_array[len];
    unsigned int m_len;
};

template<class T, unsigned int len>
inline
TStaticArray<T,len>::TStaticArray() 
: m_len(len) {
    clear();
}

template<class T, unsigned int len>
inline
TStaticArray<T, len>::TStaticArray(const TStaticArray<T, len> &rhs)
: m_len(rhs.m_len) {
    static_assert(m_len == rhs.m_len);

    for (unsigned int i = 0; i < m_len; ++i) {
        m_array[i] = rhs.m_array[i];
    }
}

template<class T, unsigned int len>
inline
TStaticArray<T, len>::~TStaticArray() {
    // empty
}

template<class T, unsigned int len>
inline
void TStaticArray<T, len>::clear() {
    ::memset(m_array, 0, sizeof(T) * m_len);
}

template<class T, unsigned int len>
inline
void TStaticArray<T, len>::set(unsigned int index, T value) {
    assert(index < m_len);

    m_array[index] = value;
}

template<class T, unsigned int len>
inline
unsigned int TStaticArray<T, len>::size() const {
    return m_len;
}

template<class T, unsigned int len>
inline
T TStaticArray<T, len>::operator[](unsigned int index) const {
    assert(index < m_len);

    return m_array[index];
}

template<class T, unsigned int len>
inline
T &TStaticArray<T, len>::operator[](unsigned int index) {
    return m_array[index];
}

template<class T, unsigned int len>
inline
bool TStaticArray<T, len>::operator == (const TStaticArray<T, len> &rhs) const {
    for (unsigned int i = 0; i < m_len; ++i) {
        if (m_array[i] != rhs.m_array[i]) {
            return false;
        }
    }

    return true;
}

template<class T, unsigned int len>
inline
TStaticArray<T, len> &TStaticArray<T, len>::operator = (const TStaticArray<T, len> &rhs) {
    if (*this == rhs) {
        return *this;
    }

    for (unsigned int i = 0; i < m_len; ++i) {
        m_array[i] = rhs.m_array[i];
    }

    return *this;
}

}
