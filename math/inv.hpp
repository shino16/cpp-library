#pragma once
#include "prelude.hpp"

template <class T>
T inverse(int k) {
  static vector<T> inv = {T(0), T(1)};
  if (inv.size() <= k) {
    int l = inv.size();
    inv.resize(k + 1);
    rep2(i, l, k + 1) inv[i] = -inv[T::mod() % i] * (T::mod() / i);
  }
  return inv[k];
}
