/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2021 Kim Kulling

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
#include <cassert>

namespace CPPCore {

//-------------------------------------------------------------------------------------------------
///	@class		TBitField
///	@ingroup	CPPCore
///
///	@brief  
//-------------------------------------------------------------------------------------------------
template <class T>
class TBitField {
public:
    TBitField();
    TBitField(T init);
    ~TBitField();
    T GetMask() const;
    bool getBit(size_t pos) const;
    void setBit(size_t pos, bool on);
    void setBit(size_t pos);
    void clearBit(size_t pos);
    void clear();
    size_t maxBits() const;

private:
    T mBitMask;
};

template <class T>
inline TBitField<T>::TBitField() :
        mBitMask(0) {
    // empty
}

template <class T>
inline TBitField<T>::TBitField(T init) :
        mBitMask(init) {
    // empty
}


template <class T>
inline TBitField<T>::~TBitField() {
    clear();
}

template <class T>
inline T TBitField<T>::GetMask() const {
    return mBitMask;
}

template <class T>
inline bool TBitField<T>::getBit(size_t pos) const {
    assert(pos < maxBits());
    return (mBitMask & (1 << pos)) != 0; // 1
}

template <class T>
inline void TBitField<T>::setBit(size_t pos, bool on) {
    assert(pos < maxBits());
    if (on) {
        setBit(pos);
    } else {
        clearBit(pos);
    }
}

template <class T>
inline void TBitField<T>::setBit(size_t pos) {
    assert(pos < maxBits());
    mBitMask = mBitMask | 1 << pos; // 2
}

template <class T>
inline void TBitField<T>::clearBit(size_t pos) {
    assert(pos < maxBits());
    mBitMask = mBitMask & ~(1 << pos); // 3
}

template <class T>
inline void TBitField<T>::clear() {
    mBitMask = 0;
}

template <class T>
inline size_t TBitField<T>::maxBits() const {
    constexpr size_t numBits = sizeof(T) * 8;
    return numBits;
}

} // namespace CPPCore
