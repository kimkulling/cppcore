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

namespace cppcore {

    typedef int32_t (*ComparisonFn)(const void* _lhs, const void* _rhs);

    template<class T>
    inline int32_t compAscending(const void *lhs, const void *rhs)  {
        const T _lhs = *static_cast<const T *>(lhs);
        const T _rhs = *static_cast<const T *>(rhs);
        return (_lhs > _rhs) - (_lhs < _rhs);
    }

    template <typename Ty>
    inline int32_t compDescending(const void *_lhs, const void *_rhs) {
        return compAscending<Ty>(_rhs, _lhs);
    }

    template<class T>
    inline void swap(T& v1, T& v2) {
        T tmp = v1;
        v1 = v2;
        v2 = tmp;
    }

    inline void swap(uint8_t &lhs, uint8_t &rhs) {
        uint8_t tmp = lhs;
        lhs = rhs;
        rhs = tmp;
    }

    inline void swap(void *v1, void *v2, size_t stride) {
        uint8_t *lhs = (uint8_t*) v1;
        uint8_t *rhs = (uint8_t*) v2;
        const uint8_t *end = rhs + stride;
        while (rhs != end) {
            swap(*lhs++, *rhs++);
        }
    }

    inline void quicksortImpl(void *pivot, void *_data, size_t num, size_t stride, ComparisonFn func) {
        if (num < 2) {
            return;
        }

        if (_data == nullptr) {
            return;
        }

        uint8_t *data = (uint8_t*) _data;
        memcpy(pivot, &data[0], stride);

        size_t l = 0;
        size_t g = 1;
        for (size_t i=1; i<num;) {
            int32_t result = func(&data[i*stride], pivot);
            if (result > 0) {
                swap(&data[l*stride], &data[i*stride], stride);
                ++l;
            } else if (result == 0) {
                swap(&data[g*stride], &data[i*stride], stride);
                ++g;
                ++i;
            } else  {
                ++i;
            }
        }
        
        quicksortImpl(pivot, &data[0], l, stride, func);
        quicksortImpl(pivot, &data[g*stride], num - g, stride, func);
    }

    inline void quicksort(void *_data, size_t num, size_t stride, ComparisonFn func) {
        uint8_t *pivot = (uint8_t*) CPPCORE_STACK_ALLOC(stride);
        quicksortImpl(pivot, _data, num, stride, func);
    }

    bool isSorted(const void *data, size_t num, size_t stride, ComparisonFn func) {
        if (num  < 2) {
            return true;
        }
        uint8_t *data_ = (uint8_t *)data;
        for (size_t i=1; i<num; ++i) {
            const int32_t result = func(&data_[(i-1)*stride], &data_[i * stride]);
            if (result == -1) {
                return false;
            }
        }

        return true;
    }

    inline int32_t binSearchImpl(void *key, void *data, size_t num, size_t stride, ComparisonFn func) {
        size_t offset = 0;
        uint8_t *_data = (uint8_t *)data;
        for (size_t i = num; offset < i;) {
            size_t idx = (offset + i) / 2;
            int32_t result = func(key, &_data[i * stride]);
            if (result < 0) {
                i = idx;
            } else if (result > 0) {
                offset = idx + 1;
            } else {
                return idx;
            }
        }
        return ~offset;
    }

    int32_t binSearch(int32_t key, int32_t* array, size_t num, ComparisonFn func) {
        return binSearchImpl(&key, &array[0], num, sizeof(int32_t), func);
    }
} // namespace cppcore
