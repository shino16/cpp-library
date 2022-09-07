#pragma once
#include "types.hpp"

// Pivots are not 1
// Not echelon form
// Entries below pivots are 0
// Returns pivots and rank
template <class T>
pair<vector<int>, int> row_unreduced(vector<vector<T>>& a) {
  int n = a.size(), m = a[0].size();
  vector<int> pivots(n);
  int i = 0, j = n;
  while (i != j) {
    rep(k, i) if (a[i][pivots[k]] != T(0)) {
      T r = a[i][pivots[k]] / a[k][pivots[k]];
      rep(j, a[i].size()) a[i][j] -= a[k][j] * r;
    }
    int p = 0;
    while (p < m && a[i][p] == T(0)) p++;
    if (p < m) pivots[i++] = p;
    else swap(a[i], a[--j]), pivots[j] = p;
  }
  return make_pair(move(pivots), i);
}

// Returns pivots and rank
template <class T>
pair<vector<int>, int> row_reduce(vector<vector<T>>& a) {
  vector<int> pivots;
  int rank;
  tie(pivots, rank) = row_unreduced(a);
  rep(i, rank) {
    T r = T(1) / a[i][pivots[i]];
    rep2(j, pivots[i], a[i].size()) a[i][j] *= r;
    rep(i2, i) if (a[i2][pivots[i]] != T(0)) {
      r = a[i2][pivots[i]];
      rep2(j, pivots[i], a[i].size()) a[i2][j] -= a[i][j] * r;
    }
  }
  rep(i, rank) rep(j, i) {
    if (pivots[j] < pivots[j + 1]) break;
    swap(pivots[j], pivots[j + 1]);
    swap(a[j], a[j + 1]);
  }
  return make_pair(pivots, rank);
}
