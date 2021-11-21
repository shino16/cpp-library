#pragma once
#include "prelude.hpp"

template <class T>
__attribute__ ((target ("popcnt"))) int popcnt(T a) {
    if constexpr (sizeof(T) <= sizeof(int)) {
        return __builtin_clz((int)a);
    } else if constexpr (sizeof(T) <= sizeof(ll)) {
        return __builtin_clzll((ll)a);
    } else if constexpr (sizeof(T) <= sizeof(ll) * 2) {
        return popcnt((ll)a) + popcnt((ll)(a >> sizeof(ll) * 8));
    }
}
