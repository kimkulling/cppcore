#pragma once

#include <cppcore/CPPCoreCommon.h>

namespace cppcore {

    typedef int32_t (*ComparisonFn)(const void* _lhs, const void* _rhs);

    int32_t int_comp(const void *lhs, const void *rhs)  {
        int32_t _lhs=0, _rhs=0;
        memcpy(&_lhs, lhs, sizeof(int32_t));
        memcpy(&_rhs, rhs, sizeof(int32_t));
        if (_lhs > _rhs) {
            return 1;
        } else if (lhs == rhs) {
            return 0;
        }
        return -1;
    }

    template<class T>
    void swap(T *v1, T *v2) {
        T tmp = *v1;
        *v1 = *v2;
        *v2 = *tmp;
    }

    inline void quicksort(void *pivot, void *_data, size_t num, ComparisonFn func=int_comp) {
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
                swap(&data[l], &data[i]);
                ++l;
            } else if (result == 0) {
                swap(&data[g], &data[i]);
                ++g;
                ++i;
            } else  {
                ++i;
            }
        }
        
        quicksort(pivot, &data[0], l, func);
        quicksort(pivot, &data[g], num-g, func);
    }

    bool isSorted(void *data, size_t num, ComparisonFn func) {
        if (num  < 2) {
            return true;
        }

        for (size_t i=0; i<num-1; ++i) {
            const int32_t result = func(&data[i], &data[i+1]);
            if (result == -1) {
                return false;
            }
        }

        return true;
    }

} // namespace cppcore
