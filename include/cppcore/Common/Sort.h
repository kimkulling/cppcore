#pragma once

#include <cppcore/CPPCoreCommon.h>

namespace cppcore {

    typedef int32_t (*ComparisonFn)(const void* _lhs, const void* _rhs);

    template<class T>
    int32_t compAscending(const void *lhs, const void *rhs)  {
        const T _lhs = *static_cast<const T *>(lhs);
        const T _rhs = *static_cast<const T *>(rhs);
        return (_lhs > _rhs) - (_lhs < _rhs);
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

    inline void quicksort(void *pivot, void *_data, size_t num, size_t stride, ComparisonFn func) {
        if (num < 2) {
            return;
        }

        if (_data == nullptr) {
            return;
        }

        size_t l = 0;
        size_t g = 1;
        uint8_t *data = (uint8_t*) _data;
        for (size_t i=1; i<num;) {
            int32_t result = func(&data[i], pivot);
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
        
        quicksort(pivot, &data[0], l, stride, func);
        quicksort(pivot, &data[g], num - g, stride, func);
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

} // namespace cppcore
