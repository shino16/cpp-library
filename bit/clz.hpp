#pragma once
#include "prelude.hpp"

template <class T>
__attribute__ ((target ("lzcnt"))) int clz(T x) {
    if (!x) return sizeof(T) * 8;
    if constexpr (sizeof(T) <= sizeof(unsigned)) {
        return __builtin_clz((unsigned)x);
    } else if constexpr (sizeof(T) <= sizeof(unsigned long long)) {
        return __builtin_clzll((unsigned long long)x);
    } else if constexpr (sizeof(T) <= sizeof(unsigned long long) * 2) {
        int l = clz((unsigned long long)(x >> sizeof(unsigned long long) * 8));
        return l != sizeof(unsigned long long) * 8 ? l : l + clz((unsigned long long)x);
    }
}
