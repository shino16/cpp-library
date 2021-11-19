#pragma once
#include "prelude.hpp"

template <class T>
__attribute__ ((target ("popcnt"))) int popcnt(T a) {
    if constexpr (sizeof(T) <= sizeof(uint)) {
        return __builtin_clz((uint)a);
    } else if constexpr (sizeof(T) <= sizeof(ull)) {
        return __builtin_clzll((ull)a);
    } else if constexpr (sizeof(T) <= sizeof(ull) * 2) {
        return popcnt((ull)a) + popcnt((ull)(a >> sizeof(ull) * 8));
    }
}
