#pragma once
#include "prelude.hpp"

#pragma GCC target("popcnt")

template <class T>
int popcnt(T a) {
  if constexpr (sizeof(T) <= sizeof(unsigned)) {
    return __builtin_popcount((unsigned)a);
  } else if constexpr (sizeof(T) <= sizeof(unsigned long long)) {
    return __builtin_popcountll((unsigned long long)a);
  } else if constexpr (sizeof(T) <= sizeof(unsigned long long) * 2) {
    return popcnt((unsigned long long)a) +
           popcnt((unsigned long long)(a >> sizeof(unsigned long long) * 8));
  }
}
