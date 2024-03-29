#pragma once

#include "bit/ctz.hpp"

template <class T>
void zeta(vector<T>& v) {
  for (int h = 1; h < v.size(); h <<= 1)
    for (int i = 0; i < v.size(); i += h * 2)
      rep2(j, i, i + h) v[j + h] += v[j];
}

template <class T>
void zeta_r(vector<T>& v) {
  for (int h = 1; h < v.size(); h <<= 1)
    for (int i = 0; i < v.size(); i += h * 2)
      rep2(j, i, i + h) v[j] += v[j + h];
}

template <class T>
void moebius(vector<T>& v) {
  for (int h = 1; h < v.size(); h <<= 1)
    for (int i = 0; i < v.size(); i += h * 2)
      rep2(j, i, i + h) v[j + h] -= v[j];
}

template <class T>
void moebius_r(vector<T>& v) {
  for (int h = 1; h < v.size(); h <<= 1)
    for (int i = 0; i < v.size(); i += h * 2)
      rep2(j, i, i + h) v[j] -= v[j + h];
}

namespace atcoder::internal {
struct modint_base;
}

template <class T>
void hadamard(vector<T>& v, bool inv = false) {
  for (int h = 1; h < v.size(); h <<= 1)
    for (int i = 0; i < v.size(); i += h * 2)
      rep2(j, i, i + h) tie(v[j], v[j + h]) =
          pair(v[j] + v[j + h], v[j] - v[j + h]);
  if (inv) {
    if constexpr (is_base_of_v<atcoder::internal::modint_base, T>) {
      T c = T(v.size()).inv();
      rep(i, v.size()) v[i] *= c;
    } else {
      int n = ctz(v.size());
      rep(i, v.size()) v[i] >>= n;
    }
  }
}
