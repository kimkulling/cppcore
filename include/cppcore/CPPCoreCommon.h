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
#  define TAG_DLL_EXPORT __declspec(dllexport)
#  define TAG_DLL_IMPORT __declspec(dllimport )
#  ifdef CPPCORE_BUILD
#    define DLL_CPPCORE_EXPORT TAG_DLL_EXPORT
#  else
#    define DLL_CPPCORE_EXPORT TAG_DLL_IMPORT
#  endif
#else
#  define DLL_CPPCORE_EXPORT
#endif
}

#endif // CPPCORE_COMMON_H_INC
