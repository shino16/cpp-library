#pragma once
#include "prelude.hpp"

template <class T, int N>
class flat_ndvec {
 public:
  flat_ndvec(const int (&dim)[N], const T& elt = T())
      : data(accumulate(dim, dim + N, 1, multiplies()), elt) {
    for (int i = N, c = 1; i--;) factor[i] = c, c *= dim[i];
  }
  auto begin() { return data.begin(); }
  auto begin() const { return data.begin(); }
  auto end() { return data.end(); }
  auto end() const { return data.end(); }
  T& operator[](const int (&is)[N]) {
    int idx = 0;
    for (int i = 0; i < N; i++) idx += factor[i] * is[i];
    return data[idx];
  }
  const T& operator[](const int (&is)[N]) const {
    int idx = 0;
    for (int i = 0; i < N; i++) idx += factor[i] * is[i];
    return data[idx];
  }

 private:
  array<int, N> factor;
  vector<T> data;
};
