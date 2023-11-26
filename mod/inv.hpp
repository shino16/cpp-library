#pragma once
#include "prelude.hpp"
// #include "mod/modint.hpp"
#include <atcoder/modint>

template <class T = atcoder::modint998244353>
T inverse(int n) {
  static vector<T> v = {T(0), T(1)};
  while (v.size() <= n) {
    v.push_back(-v[T::mod() % v.size()] * (T::mod() / v.size()));
  }
  return v[n];
}
