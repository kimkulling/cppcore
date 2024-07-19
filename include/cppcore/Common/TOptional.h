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

namespace cppcore {

//-------------------------------------------------------------------------------------------------
///	@class		TOptional
///	@ingroup	CPPCore
///
///	@brief  This class is used to describe a value which is not valid until it will ge inited.
//-------------------------------------------------------------------------------------------------
template<class T>
class TOptional {
public:
    /// @brief  The class constructor.
    /// @param[in]  defaultValue    Init value if no set was performed.
    TOptional(T defaultValue);

    /// @brief  The class destructor.
    ~TOptional() = default;

    /// @brief  Will return false, if the value was not set,
    /// @return The init state.
    bool isInited() const;

    /// @brief  Will return the value or the default value if no init was performed before.
    /// @return The value or the default value.
    T value();

    /// @brief  Will set the value, the instance will be in init state true afterwards.
    /// @param[in]  value   The value.
    void set(T value);

    /// Default operators.
    T &operator = ( const T &value);

    /// The copy constructor.
    bool operator == (const TOptional<T> &rhs) const;

private:
    T mValue;
    bool mInited;
};

template<class T>
inline TOptional<T>::TOptional(T defaultValue) :
        mValue(defaultValue),
        mInited(false) {
    // empty
}

template<class T>
bool inline TOptional<T>::isInited() const {
    return mInited;
}

template<class T>
T inline TOptional<T>::value() {
    if (mInited) {
        return mValue;
    }

    return T{};
}

template<class T>
void inline TOptional<T>::set(T value) {
    assert(!mInited);

    mValue = value;
    mInited = true;
}

template<class T>
inline T &TOptional<T>::operator = (const T &value) {
    mValue = value;
    if(!mInited) {
        mInited = true;
    }

    return *this;
}

template<class T>
inline bool TOptional<T>::operator == (const TOptional &rhs) const {
    if (mInited == rhs.isInited) {
        if (!mInited) {
            return true;
        }

        return mValue == rhs.mValue;
    }
    return false;
}

} // namespace cppcore
