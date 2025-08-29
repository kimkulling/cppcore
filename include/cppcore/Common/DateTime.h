/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2025 Kim Kulling

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
#include <ctime>

namespace cppcore {

//-------------------------------------------------------------------------------------------------
///	@class		DateTime
///	@ingroup	CPPCore
///
///	@brief  This class is used to get the current date and time.
//-------------------------------------------------------------------------------------------------
struct DateTime {
    uint32_t year{};    ///< The current year
    uint32_t month{};   ///< The current month
    uint32_t day{};     ///< The current day
    uint32_t hour{};    ///< The current hour
    uint32_t minute{};  ///< The current minute
    uint32_t second{};  ///< The current second

    /// @brief The class constructor.
    DateTime() {
        time_t timestamp = ::time(nullptr);
        tm dt{}; 
#if defined(_WIN32)
        ::localtime_s(&dt, &timestamp);
+#else
        ::localtime_r(&timestamp, &dt);
+#endif        year = dt.tm_year + 1900;
        month   = dt.tm_mon;
        day     = dt.tm_mday;
        hour    = dt.tm_hour;
        minute  = dt.tm_min;
        second  = dt.tm_sec;
    }
};

} // namespace cppcore 

