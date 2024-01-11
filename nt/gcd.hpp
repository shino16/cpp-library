#pragma once
#include "bit/ctz.hpp"

template <class T>
T gcd(T u, T v) {
  u = abs(u), v = abs(v);
  if (u == 0) return v;
  if (v == 0) return u;
  int i = ctz(u); u >>= i;
  int j = ctz(v); v >>= j;
  int k = min(i, j);
  while (true) {
    if (u > v) swap(u, v);
    v -= u;
    if (v == 0) return u << k;
    v >>= ctz(v);
  }
}
