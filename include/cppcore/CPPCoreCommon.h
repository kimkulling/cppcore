/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2019 Kim Kulling

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

#include <cstddef>
#include <cassert>
#include <cinttypes>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>

namespace cppcore {

#if defined( _WIN32 ) || defined( _WIN64 )
#   define CPPCORE_WINDOWS
#   define _CRT_SECURE_NO_WARNINGS
#elif defined(__gnu_linux__)
#   define CPPCORE_GNU_LINUX
#elif defined(__APPLE__) || defined(__MACH__)
#   define CPPCORE_IOS
#else
#   error "Unsupported operation system."
#endif

#ifdef CPPCORE_WINDOWS
#   define CPPCORE_TAG_DLL_EXPORT __declspec(dllexport)
#   define CPPCORE_TAG_DLL_IMPORT __declspec(dllimport )
#   ifdef CPPCORE_BUILD
#       define DLL_CPPCORE_EXPORT CPPCORE_TAG_DLL_EXPORT
#   else
#        define DLL_CPPCORE_EXPORT CPPCORE_TAG_DLL_IMPORT
#   endif
    // All disabled warnings for windows
#   pragma warning( disable : 4251 ) // <class> needs to have dll-interface to be used by clients of class <class>
#else
#   define DLL_CPPCORE_EXPORT __attribute__((visibility("default")))
#endif

//-------------------------------------------------------------------------------------------------
/// @fn ContainerClear
///
/// @brief  Will release a CPPCore-specific container with a simple delete.
/// @param  ctr     [in] A reference to the container to release.
//-------------------------------------------------------------------------------------------------
template<class T>
void ContainerClear( T & ctr, void( *DeleterFunc )( T & ) = nullptr ) {
    if( ctr.isEmpty() ) {
        return;
    }

    if ( nullptr == DeleterFunc ) {
        for ( size_t i = 0; i < ctr.size(); ++i ) {
            delete ctr[ i ];
        }
    } else { 
        DeleterFunc( ctr );
    }
    ctr.clear();
}

//-------------------------------------------------------------------------------------------------
/// @def    CPPCORE_NONE_COPYING
///
/// @brief  This macro marks a class a not copyable.
/// @param  name    [in] The name of the class.
//-------------------------------------------------------------------------------------------------
#define CPPCORE_NONE_COPYING( name ) \
public: \
    name( const name & ) = delete ;\
    name( name && ) = delete; \
    name &operator = ( const name & ) = delete;

//-------------------------------------------------------------------------------------------------
/// @def    CPPCORE_ARRAY_SIZE
///
/// @brief  This macro calculates the number of items inside of an array.
/// @param  x    [in] The array to get the number of items.
///	@remark Be careful, use it as following:
///	@code
///	int array[] = {1,2,3,4}; CPPCORE_ARRAY_SIZE( array );  // correct
/// void foo( int array[] ) { CPPCORE_ARRAY_SIZE( array ); // not correct
/// @endcode
//-------------------------------------------------------------------------------------------------
#define CPPCORE_ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

} // Namespace cppcore
