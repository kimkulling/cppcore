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
#include <string.h>
#include <cinttypes>

namespace cppcore {

#define ALIGN_MASK(value, mask) (((value) + (mask)) & ((~0) & (~(mask))))

template<class T>
inline size_t align(size_t n) {
    return (n + sizeof(T) - 1) & ~(sizeof(T) - 1);
}

//-------------------------------------------------------------------------------------------------
///	@class		THashMap
///	@ingroup	CPPCore
///
///	@brief  Utility class for common memory operations.
//-------------------------------------------------------------------------------------------------
class DLL_CPPCORE_EXPORT MemUtils {
public:
    /// @brief  Will clear the given buffer with zero.
    /// @param[inout] buffer    The buffer to clear.
    static void clearMemory(void *buffer, size_t size);

    ///	@brief Will return true, if the pointer fits into the alignment.
    ///	@param[in] ptr          The pointer to check.
    /// @param[in] align        The alignment to check for.
    /// @return true if aligned, false if not.
    static bool isAligned(const void *ptr, size_t align);

    ///	@brief  Will align the given pointer.
    /// @param[in] ptr          The pointer to align.
    /// @param[in] extra        Space for headers / meta information.
    /// @param[in] align        The alignment to check for.
    /// @return The aligned pointer.
    static const void *alignPtr(void *ptr, size_t extra, size_t align);

    ///	@brief The default class constructor.
    MemUtils() = default;

    /// @brief The class destructor.
    ~MemUtils() = default;
};

inline bool MemUtils::isAligned(const void *ptr, size_t align) {
    union {
        const void *mPtr;
        uintptr_t mAddr;
    } unaligned;

    unaligned.mPtr = ptr;
    return 0 == (unaligned.mAddr & (align - 1));
}

inline const void *MemUtils::alignPtr(void *ptr, size_t extra, size_t align) {
     if (align == 0) {
        return nullptr;
    }
    union {
        const void *mPtr;
        uintptr_t mAddr;
    } unaligned;
    unaligned.mPtr = ptr;
    uintptr_t un = unaligned.mAddr + extra; // space for header
    const uintptr_t mask = align - 1;
    uintptr_t aligned = ALIGN_MASK(un, mask);
    unaligned.mAddr = aligned;

    return unaligned.mPtr;
}

} // Namespace cppcore
