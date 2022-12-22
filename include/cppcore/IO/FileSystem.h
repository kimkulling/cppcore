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

#ifdef WIN32
#include <Windows.h>
#else
#include <sys/statvfs.h>
#endif

namespace cppcore {

/// @brief  The file-system space info.
struct FSSpace {
    long capacity;  ///< The capacity in total.
    long free;      ///< The free capacity
    long inUse;     ///< The used capacity

    /// @brief  The default class constructor.
    FSSpace() :
            capacity(0L), free(0L), inUse(0L) {
        // empty
    }
};

/// @brief  This class provides some common OS-specific file operations.
class FileSystem {
public:
    /// @brief  The class constructor with the location.
    /// @param[in] location     The root location.
    FileSystem(const char *location);
    
    /// @brief  The class destructor.
    ~FileSystem() = default;
    
    /// @brief  Will perform a refresh.
    void refresh();
    
    /// @brief  Will return the free disk info.
    /// @return the File-system space.
    FSSpace *getFreeDiskSpace();

private:
    const char *m_drive;
    FSSpace m_fsSpace;
};

inline FileSystem::FileSystem(const char *location) :
        m_drive(location),
        m_fsSpace() {
    // empty
}

inline void FileSystem::refresh() {
    if (m_drive == nullptr) {
        return;
    }
#ifdef WIN32
    PULARGE_INTEGER freeByteAvailable = 0, totalNumberOfBytes = 0, totalNumberOfFreeBytes = 0;
    BOOL result = ::GetDiskFreeSpaceEx(m_drive, freeByteAvailable, totalNumberOfBytes, totalNumberOfFreeBytes);
    if (TRUE == result) {
        ::memcpy(&m_fsSpace.capacity, &totalNumberOfBytes->QuadPart, sizeof(PULARGE_INTEGER));
        ::memcpy(&m_fsSpace.free, &freeByteAvailable->QuadPart, sizeof(PULARGE_INTEGER));
        ULONGLONG res = totalNumberOfBytes->QuadPart - freeByteAvailable->QuadPart;
        ::memcpy(&m_fsSpace.inUse, &res, sizeof(PULARGE_INTEGER));
    }
#else
    struct statvfs stats;
    statvfs(m_drive, &stats);
    m_fsSpace.capacity = stats.f_bsize;
    m_fsSpace.free = stats.f_bsize * stats.f_bfree;
    m_fsSpace.inUse = m_fsSpace.capacity - m_fsSpace.free;
#endif
}

inline FSSpace *FileSystem::getFreeDiskSpace() {
    refresh();

    return &m_fsSpace;
}

} // Namespace cppcore
