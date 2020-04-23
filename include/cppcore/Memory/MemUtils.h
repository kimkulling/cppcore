/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2016 Kim Kulling

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
#include <cinttypes>

namespace CPPCore {

#define ALIGN_MASK(value, mask) (((value) + (mask)) & ((~0) & (~(mask))))

//-------------------------------------------------------------------------------------------------
///	@class		THashMap
///	@ingroup	CPPCore
///
///	@brief  Utility class for common memory operations.
//-------------------------------------------------------------------------------------------------
class MemUtils {
public:
    /// @brief  Will clear the given buffer with zero.
    /// @param  buffer      [inout] The buffer to clear.
    static void clearMemory(void *buffer, size_t size);

    static bool isAligned(const void *ptr, size_t align);

    static void *alignPtr(void *ptr, size_t extra, size_t align);

    MemUtils() = delete;
    ~MemUtils() = delete;
};

inline bool MemUtils::isAligned(const void *ptr, size_t align) {
    union {
        const void *mPtr;
        uintptr_t mAddr;
    } unaligned;

    unaligned.mPtr = ptr;
    return 0 == (unaligned.mAddr & (align - 1));
}

inline void *MemUtils::alignPtr(void *ptr, size_t extra, size_t align) {
    union {
        void *mPtr;
        uintptr_t mAddr;
    } unaligned;

    unaligned.mPtr = ptr;
    uintptr_t un = unaligned.mAddr + extra; // space for header
    const uintptr_t mask = align - 1;
    uintptr_t aligned = ALIGN_MASK(un, mask);
    unaligned.mAddr = aligned;

    return unaligned.mPtr;
}

} // Namespace CPPCore
