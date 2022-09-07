#pragma once
#include "prelude.hpp"

struct inverse {
  int n;
  inverse(int n) : n(n) { }
  template <class T>
  operator T() const {
    static vector<T> inv = {T(0), T(1)};
    if (inv.size() <= n) {
      int l = inv.size();
      inv.resize(n + 1);
      rep2(i, l, n + 1) inv[i] = -inv[T::mod() % i] * (T::mod() / i);
    }
    return inv[n];
  }
};
