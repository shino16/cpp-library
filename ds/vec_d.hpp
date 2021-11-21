#pragma once
#include "prelude.hpp"

template <class T, int N>
class vec_d {
 public:
  vec_d(const int (&dim)[N], const T& elt = T())
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
  template <enable_if_t<N == 2>* = nullptr>
  T* operator[](int i) { return &data[i * factor[0]]; }
  template <enable_if_t<N == 2>* = nullptr>
  const T* operator[](int i) const { return &data[i * factor[0]]; }
  template <enable_if_t<N == 2>* = nullptr>
  T& operator[](pair<int, int> i) { return (*this)[{i.first, i.second}]; }
  template <enable_if_t<N == 2>* = nullptr>
  const T& operator[](pair<int, int> i) const { return (*this)[{i.first, i.second}]; }

 private:
  array<int, N> factor;
  vector<T> data;
};
