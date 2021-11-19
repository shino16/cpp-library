#pragma once
#include "prelude.hpp"

template <class T>
__attribute__ ((target ("bmi"))) int ctz(T x) {
    if (!x) return sizeof(T) * 8;
    if constexpr (sizeof(T) <= sizeof(int)) {
        return __builtin_ctz((uint)x);
    } else if constexpr (sizeof(T) <= sizeof(ull)) {
        return __builtin_ctzll((ull)x);
    } else if constexpr (sizeof(T) <= sizeof(ull) * 2) {
        int l = ctz((ull)x);
        return l != sizeof(ull) * 8 ? l : l + ctz((ull)(x >> sizeof(ull) * 8));
    }
}
