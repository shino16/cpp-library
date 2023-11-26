#pragma once
#include "mod/inv.hpp"

template <class T = atcoder::modint998244353>
T fact(int n) {
  static vector<T> v = {T(1)};
  while (v.size() <= n) v.push_back(v.back() * v.size());
  return v[n];
}

template <class T = atcoder::modint998244353>
T inv_fact(int n) {
  static vector<T> v = {T(1)};
  while (v.size() <= n) v.push_back(v.back() * inverse(v.size()));
  return v[n];
}
