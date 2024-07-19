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

#include <string>

namespace cppcore {

//-------------------------------------------------------------------------------------------------
/// @class      TDefaultAllocator
/// @ingroup    CPPCore
///
/// @brief  This class implements the default allocator used by all container classes of the cppcore 
/// library.
//-------------------------------------------------------------------------------------------------
template <class T>
class TDefaultAllocator {
public:
    /// @brief  The default class constructor.
    TDefaultAllocator();

    /// @brief  The class destructor.
    ~TDefaultAllocator();

    /// @brief  Will allocate the number of insances.
    /// @param[in] size   Size of instances to allocate.
    /// @return Pointer showing to the new instance or nullptr if not possible.
    T *alloc(size_t size);

    /// @brief  Will release the last item from the stack. A basic check will be performed to
    ///         ensure that it is the correct item.
    /// @param  ptr     [in] The pointer to validate.
    void release(T *ptr);

    /// @brief Will prereserve the number of instances.
    /// @param[in] size  NUmber, not used here.
    void reserve(size_t size);

    /// @brief  Will clear the whole memory, all used data will be marked as invalid.
    void clear();

    /// @brief  Returns the number of allocated instances on the stack
    /// @return The number of allocated instance.
    size_t capacity() const;

    /// @brief  Returns the allocated memory in bytes.
    /// @return The allocated memory in bytes.
    size_t reservedMem() const;

    /// @brief  Returns the free memory in bytes.
    /// @return The free memory in bytes.
    size_t freeMem() const;

    /// @brief  Will dump a statistic overview into the given string.
    /// @param  allocs  [inout] The string to hold the allocation statistic.
    void dumpAllocations(std::string &allocs);

    // To copying allowed
    CPPCORE_NONE_COPYING(TDefaultAllocator)
};

template <class T>
inline TDefaultAllocator<T>::TDefaultAllocator() {
    // empty
}

template <class T>
inline TDefaultAllocator<T>::~TDefaultAllocator() {
    // empty
}

template <class T>
inline T *TDefaultAllocator<T>::alloc(size_t size) {
    return new T[size];
}

template <class T>
inline void TDefaultAllocator<T>::release(T *ptr) {
    delete [] ptr;
}

template <class T>
inline void TDefaultAllocator<T>::reserve(size_t) {
    // empty
}

template <class T>
inline void TDefaultAllocator<T>::clear() {
    // empty
}

template <class T>
inline size_t TDefaultAllocator<T>::capacity() const {
    return 0L;
}

template <class T>
inline size_t TDefaultAllocator<T>::reservedMem() const {
    return 0L;
}

template <class T>
inline size_t TDefaultAllocator<T>::freeMem() const {
    return 0L;
}

template <class T>
inline void TDefaultAllocator<T>::dumpAllocations(std::string &allocs) {
    // empty
}

} // Namespace cppcore
