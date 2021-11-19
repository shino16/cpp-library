#pragma once
#include "prelude.hpp"

template <class T>
__attribute__ ((target ("lzcnt"))) int clz(T x) {
    if (!x) return sizeof(T) * 8;
    if constexpr (sizeof(T) <= sizeof(uint)) {
        return __builtin_clz((uint)x);
    } else if constexpr (sizeof(T) <= sizeof(ull)) {
        return __builtin_clzll((ull)x);
    } else if constexpr (sizeof(T) <= sizeof(ull) * 2) {
        uint l = clz((ull)(x >> sizeof(ull) * 8));
        return l != sizeof(ull) * 8 ? l : l + clz((ull)x);
    }
}
