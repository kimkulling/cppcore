#pragma once

#include <cppcore/CPPCoreCommon.h>

namespace CPPCore {

template<class T>
class TSharedPtr {
public:
    explicit TSharedPtr( T *ptr );
    ~TSharedPtr();
    void clear();
    T *operator ->() const;
    T &operator *() const;
    TSharedPtr<T> &operator = ( T *pPtr );
    bool operator == ( const TSharedPtr<T> &rhs ) const;
    bool operator != ( const TSharedPtr<T> &rhs ) const;

private:
    unsigned int m_refs;
    T *m_ptr;
};

template<class T>
inline
explicit TSharedPtr<T>::TSharedPtr( T *ptr ) 
: m_refs( 0 )
, m_ptr( ptr ) {
    if ( nullptr != m_ptr ) {
        m_refs++;
    }
}

template<class T>
inline
TSharedPtr<T>::~TSharedPtr() {
    // empty
}

template<class T>
inline
void TSharedPtr<T>::clear() {
    --m_refs;
    m_ptr = nullptr;
}

template<class T>
inline
T *TSharedPtr<T>::operator ->() const {
    return m_ptr;
}

template<class T>
inline
T &TSharedPtr<T>::operator *() const {
    return *m_ptr;
}

template<class T>
inline
TObjPtr<T> &TSharedPtr<T>::operator = ( T *ptr ) {
    clear();
    if ( nullptr != ptr ) {
        m_refs++;
        m_ptr = ptr;
    }

    return *this;
}

template<class T>
inline
bool TSharedPtr<T>::operator == ( const TSharedPtr<T> &rhs ) const {
    if ( rhs.m_ptr == m_ptr ) {
        return true;
    }
    return false;
}

template<class T>
inline
bool TSharedPtr<T>::operator != ( const TSharedPtr<T> &rhs ) const {
    return !( *this == rhs );
}

} // Namespace CPPCore
