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

#include <memory>

namespace cppcore {
    
//-------------------------------------------------------------------------------------------------
///	@class		RandomGenerator
///	@ingroup	CPPCore
///
///	@brief  This class is used to wrap different random number generators.
//-------------------------------------------------------------------------------------------------
class DLL_CPPCORE_EXPORT RandomGenerator {
public:
    /// @brief  This enum describes the requested random generator.
    enum class GeneratorType {
        Standard,           ///< The default c+++ generator.
        MersenneTwister     ///< The MersenneTwister algorithm
    };
    
    /// @brief  The class constructor.
    /// @param  type    [in] The requested generator.
    RandomGenerator( GeneratorType type = GeneratorType::Standard ) noexcept;

    /// @brief  The class destructor.
    ~RandomGenerator();

    /// @brief  Gets a new random number.
    /// @param  lower   [in] The lower bound.
    /// @param  upper   [in] The upper bound.
    /// @return A new random number.
    int get( int lower, int upper );

    // Copying is not allowed
    RandomGenerator(const RandomGenerator &) = delete;
    RandomGenerator &operator = (const RandomGenerator &) = delete;

private:
    GeneratorType m_type;
};

} // Namespace cppcore
