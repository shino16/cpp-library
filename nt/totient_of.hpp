#pragma once
#include "prelude.hpp"
#include "bit/ctz.hpp"

template <class T>
T totient_of(T n) {
  T res = n;
  if (n % 2 == 0) {
    res /= 2;
    n >>= ctz(n);
  }
  for (int p = 3; p * p <= n; p++) if (n % p == 0) {
    res -= res / p;
    while (n % p == 0) n /= p;
  }
  if (n != 1) res -= res / n;
  return res;
}
