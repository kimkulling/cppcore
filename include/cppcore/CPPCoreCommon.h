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

#include <cstddef>
#include <string.h>

namespace CPPCore {

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

//-------------------------------------------------------------------------------------------------
/// @fn ContainerClear
///
/// @brief  Will release a container with a simple delete.
/// @param  ctr     [in] A reference to the container to release.
//-------------------------------------------------------------------------------------------------
template<class T>
void ContainerClear( T & ctr ) {
    if( ctr.isEmpty() ) {
        return;
    }

    for( size_t i = 0; i < ctr.size(); ++i ) {
        delete ctr[ i ];
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
private:\
    name( const name & );\
    name &operator = ( const name & );

//-------------------------------------------------------------------------------------------------

} // Namespace CPPCore

#endif // CPPCORE_COMMON_H_INC
