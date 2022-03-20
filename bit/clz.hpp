#pragma once
#include "prelude.hpp"

template <class T>
__attribute__ ((target ("lzcnt"))) int clz(T x) {
    if (!x) return sizeof(T) * 8;
    if constexpr (sizeof(T) <= sizeof(int)) {
        return __builtin_clz((int)x);
    } else if constexpr (sizeof(T) <= sizeof(ll)) {
        return __builtin_clzll((ll)x);
    } else if constexpr (sizeof(T) <= sizeof(ll) * 2) {
        int l = clz((ll)(x >> sizeof(ll) * 8));
        return l != sizeof(ll) * 8 ? l : l + clz((ll)x);
    }
}
