#pragma once
#include "prelude.hpp"

template <class T>
T floor_sqrt(T n) {
  if (n == 0) return 0;
  T x = round(sqrt(n));
  return (x + n / x) / 2;
}

template <class T>
T ceil_sqrt(T n) {
  return n == 0 ? 0 : floor_sqrt(n - 1) + 1;
}
