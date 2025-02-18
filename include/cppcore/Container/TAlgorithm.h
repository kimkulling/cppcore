#pragma once

#include <cassert>

namespace cppcore {
    
template<class TIt>
inline size_t distance(TIt begin, TIt end) {
    assert(begin < end);
    const size_t distance = end - begin;
    return distance;
}

} // namespace cppcore
