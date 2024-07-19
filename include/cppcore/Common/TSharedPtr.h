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
///	@class		TSharedPtr
///	@ingroup	CPPCore
///
///	@brief  This class a shared pointer implementation.
//-------------------------------------------------------------------------------------------------
template <class T>
class TSharedPtr {
public:
    typedef void (*deleterFunc)(T *ptr);

    TSharedPtr();
    explicit TSharedPtr(T *ptr, deleterFunc func = nullptr);
    TSharedPtr(const TSharedPtr<T> &rhs);
    ~TSharedPtr();
    void reset(T *ptr, deleterFunc func = nullptr);
    void clear();
    unsigned int getRefs() const;
    T *operator->() const;
    T &operator*() const;
    TSharedPtr<T> &operator=(const TSharedPtr<T> &rhs);
    bool operator==(const TSharedPtr<T> &rhs) const;
    bool operator!=(const TSharedPtr<T> &rhs) const;

private:
    struct PtrType {
        unsigned int m_refs;
        T *m_ptr;
        deleterFunc m_delFunc;

        PtrType(T *ptr, deleterFunc func) :
                m_refs(0), m_ptr(ptr), m_delFunc(func) {
            if (nullptr != m_ptr) {
                ++m_refs;
            }
        }

        ~PtrType() {
            if (nullptr == m_delFunc) {
                delete m_ptr;
            } else {
                m_delFunc(m_ptr);
            }
        }

        PtrType() = delete;
        PtrType(const PtrType &rhs) = delete;
    };
    PtrType *m_ptrType;
};

template <class T>
inline TSharedPtr<T>::TSharedPtr() :
        m_ptrType(nullptr) {
    // empty
}

template <class T>
inline TSharedPtr<T>::TSharedPtr(T *ptr, deleterFunc func) :
        m_ptrType(nullptr) {
    m_ptrType = new PtrType(ptr, func);
}

template <class T>
inline TSharedPtr<T>::TSharedPtr(const TSharedPtr<T> &rhs) :
        m_ptrType( rhs.m_ptrType ) {
    if (nullptr != m_ptrType) {
        m_ptrType->m_refs++;
    }
}

template <class T>
inline TSharedPtr<T>::~TSharedPtr() {
    clear();
}

template <class T>
inline void TSharedPtr<T>::reset(T *ptr, deleterFunc func) {
    if (nullptr != m_ptrType) {
        clear();
    }
    m_ptrType = new PtrType(ptr, func);
}

template <class T>
inline void TSharedPtr<T>::clear() {
    if (nullptr == m_ptrType) {
        return;
    }

    m_ptrType->m_refs--;
    if (0 == m_ptrType->m_refs) {
        delete m_ptrType;
    }
    m_ptrType = nullptr;
}

template <class T>
inline unsigned int TSharedPtr<T>::getRefs() const {
    return m_ptrType->m_refs;
}

template <class T>
inline T *TSharedPtr<T>::operator->() const {
    return m_ptrType->m_ptr;
}

template <class T>
inline T &TSharedPtr<T>::operator*() const {
    return *m_ptrType->m_ptr;
}

template <class T>
inline TSharedPtr<T> &TSharedPtr<T>::operator=(const TSharedPtr<T> &rhs) {
    clear();
    m_ptrType = rhs.m_ptrType;
    m_ptrType->m_refs++;

    return *this;
}

template <class T>
inline bool TSharedPtr<T>::operator==(const TSharedPtr<T> &rhs) const {
    if (rhs.m_ptrType == m_ptrType) {
        return true;
    }
    return false;
}

template <class T>
inline bool TSharedPtr<T>::operator!=(const TSharedPtr<T> &rhs) const {
    return !(*this == rhs);
}

} // Namespace cppcore
