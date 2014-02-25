/*
-------------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014 Kim Kulling

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
-------------------------------------------------------------------------------------------------
*/
#pragma once
#ifndef CPPCORE_COMMON_H_INC
#define CPPCORE_COMMON_H_INC

namespace CPPCore {

    ///	The data type unsigned char, 1 byte long.
    typedef unsigned char uc8;

    ///	The data type signed char, 1 byte long.
    typedef char c8;

    ///	The data type unsigned short, 2 byte long.
    typedef unsigned short ui16;

    ///	The data type signed short, 2 byte long.
    typedef signed short i16;

    ///	The data type signed int, 4 byte long.
    typedef int	i32;

    ///	The data type unsigned int, 4 byte long.
    typedef unsigned short ui16;

    ///	The data type signed int, 4 byte long.
    typedef unsigned int ui32;

    ///	The data type float, 4 byte long.
    typedef float f32;

    ///	The data type double, 8 byte long.
    typedef double d32;


#ifdef _WIN32
#   define TAG_DLL_EXPORT __declspec(dllexport)
#   define TAG_DLL_IMPORT __declspec(dllimport )
#   ifdef CPPCORE_BUILD
#       define DLL_CPPCORE_EXPORT TAG_DLL_EXPORT
#   else
#        define DLL_CPPCORE_EXPORT TAG_DLL_IMPORT
#   endif
#   pragma warning( disable : 4251 )
#else
#   define DLL_CPPCORE_EXPORT
#endif

} // Namespace CPPCore

#endif // CPPCORE_COMMON_H_INC
