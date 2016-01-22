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
-------------------------------------------------------------------------------------------------*/
#include <cppcore/Common/TStringBase.h>

namespace CPPCore {

char *getTrans( unsigned int id );
        
//-------------------------------------------------------------------------------------------------
///	@class		CString
///	@ingroup	CPPCore
///
///	@brief	This string class implements a simple string
//-------------------------------------------------------------------------------------------------
class DLL_CPPCORE_EXPORT CString {
public:
    /// @brief  The default class constructor.
    CString();

    /// @brief  The class constructor with a buffer of data.
    /// @param  pStr        [in] The buffer with the data.
    CString( const char *pStr );

    /// @brief  The copy class constructor.
    /// @param  rhs         [in] String to copy.
    CString( const CString &rhs );

    /// @brief  The class destructor.
    ~CString();

    /// @brief  Returns true, if the string is empty.
    /// @return true if string is empty, else false.
    bool isEmpty() const;

    /// @brief  Returns the length of the string.
    /// @return The length.
    size_t size() const;

    /// @brief  Clears the string buffer, all buffers and data will be released.
    void clear();

    /// @brief  Returns a pointer showing to the first element of the string buffer.
    /// @return The pointer showing to the first element of the string.
    const char* c_str() const;

    char operator [] ( size_t idx ) const;
    bool operator == ( const CString &rhs ) const;
    bool operator != ( const CString &rhs ) const;
    CString &operator = ( const CString &rhs );

private:
    TStringBase<char> m_string;
};

//-------------------------------------------------------------------------------------------------

} // Namespace CPPCore
