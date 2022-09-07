#pragma once
#include "prelude.hpp"

template <class T>
T floor_sqrt(T x) {
  if (x == 0) return 0;
  T s = round(sqrt(x));
  return (s + x / s) / 2;
}

template <class T>
T ceil_sqrt(T x) {
  return x == 0 ? 0 : floor_sqrt(x - 1) + 1;
}
