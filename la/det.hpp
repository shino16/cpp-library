#pragma once
#include "la/row_reduce.hpp"

// Row-reduces a
template <class T>
T determinant(vector<vector<T>>& a) {
  auto [pivots, rank] = row_unreduced(a);
  if (rank < a.size()) return T(0);
  T res(1);
  rep(i, a.size()) res *= a[i][pivots[i]];
  return res;
}
