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
#include <cppcore/Random/RandomGenerator.h>

#include <stdlib.h>
#include <time.h>
#include <cassert>

namespace cppcore {

static const unsigned int N = 624;
static const unsigned int M = 397;

static void mersenne_twister_vector_init( unsigned int *seedPoints, size_t len ) {
    assert( nullptr != seedPoints );

    const unsigned int mult = 1812433253ul;
    unsigned int       seed = 5489ul;
    for (size_t i = 0; i < len; ++i) {
        seedPoints[ i ] = seed;
        seed = mult * (seed ^ (seed >> 30)) + (static_cast<unsigned int>(i) + 1);
    }
}

static void mersenne_twister_vector_update(unsigned int* const p) {
    static const unsigned int A[ 2 ] = { 0, 0x9908B0DF };
    unsigned int i=0;
    for (; i < N - M; i++) {
        p[i] = p[i + (M)] ^ (((p[i] & 0x80000000) | (p[i + 1] & 0x7FFFFFFF)) >> 1) ^ A[p[i + 1] & 1];
    }
    for (; i < N - 1; i++) {
        p[i] = p[i + (M - N)] ^ (((p[i] & 0x80000000) | (p[i + 1] & 0x7FFFFFFF)) >> 1) ^ A[p[i + 1] & 1];
    }
    p[N - 1] = p[M - 1] ^ (((p[N - 1] & 0x80000000) | (p[0] & 0x7FFFFFFF)) >> 1) ^ A[p[0] & 1];
}

unsigned int mersenne_twister() {
    // State-vector
    static unsigned int  vector[ N ];   
    // readout index
    static int           idx = N + 1;

    if (static_cast<unsigned int>(idx) >= N) {
        if (static_cast<unsigned int>(idx) > N) {
            mersenne_twister_vector_init(vector, N);
        }
        mersenne_twister_vector_update(vector);
        idx = 0;
    }
    unsigned int e = vector[ idx++ ];
    
    // Tempering
    e ^= (e >> 11);             
    e ^= (e << 7)  & 0x9D2C5680;
    e ^= (e << 15) & 0xEFC60000;
    e ^= (e >> 18);

    return e;
}

RandomGenerator::RandomGenerator( GeneratorType type ) noexcept :
        m_type( type ) {
    ::srand( static_cast<unsigned int>(time(nullptr)));
}

RandomGenerator::~RandomGenerator() {
    // empty
}

int RandomGenerator::get( int lower, int upper ) {
    int ret( 0 );
    if ( GeneratorType::Standard == m_type ) {
        ret = ::rand() % upper + lower;
    } else if (GeneratorType::MersenneTwister == m_type) {
        ret = mersenne_twister() % upper + lower;
    }

    return ret;
}

} // Namespace cppcore
