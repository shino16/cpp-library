#pragma once
#include "prelude.hpp"

template <class T>
__attribute__((target("bmi"))) int ctz(T x) {
  if (!x) return sizeof(T) * 8;
  if constexpr (sizeof(T) <= sizeof(unsigned)) {
    return __builtin_ctz((unsigned)x);
  } else if constexpr (sizeof(T) <= sizeof(unsigned long long)) {
    return __builtin_ctzll((unsigned long long)x);
  } else if constexpr (sizeof(T) <= sizeof(unsigned long long) * 2) {
    unsigned long long y = x;
    return y ? ctz(y)
             : sizeof(y) * 8 + ctz((unsigned long long)(x >> sizeof(y) * 8));
  }
}
