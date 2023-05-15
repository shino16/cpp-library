#pragma once
#include "prelude.hpp"

// Returns (g, x, y) with ax + by = g, 0 <= x < b/g
template <class T>
tuple<T, T, T> extgcd(T a0, T b0) {
  // a - a0 x - b0 y = 0
  // b - a0 u - b0 v = 0
  T a = a0, b = b0;
  T x = 1, u = 0;
  while (b) {
    T q = a / b;
    swap(a -= q * b, b);
    swap(x -= q * u, u);
  }
  if (x < 0) x += b0 / a;
  T y = (a - a0 * x) / b0;
  return {a, x, y};
}
