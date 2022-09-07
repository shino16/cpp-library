#pragma once
#include "la/row_reduce.hpp"

// a: row reduced echelon form
template <class T>
vector<vector<T>> ker_basis(const vector<vector<T>>& a, const vector<int>& pivots, int rank) {
  int m = a[0].size();
  vector<vector<T>> res;
  vector<int> ps = {-1};
  rep(i, rank) ps.push_back(pivots[i]);
  ps.push_back(m);
  rep(h, ps.size() - 1) {
    rep2(j, ps[h] + 1, ps[h + 1]) {
      vector<T> x(m);
      x[j] = -T(1);
      rep(i, h) x[pivots[i]] = a[i][j];
      res.push_back(move(x));
    }
  }
  return res;
}

template <class T>
std::optional<pair<vector<T>, vector<vector<T>>>> solve(vector<vector<T>> a, vector<T> b) {
  int n = a.size(), m = a[0].size();
  rep(i, n) a[i].push_back(b[i]);
  auto [pivots, rank] = row_reduce(a);
  rep(i, n) if (pivots[i] == m) return nullopt;
  vector<T> c(n);
  repr(i, rank) c[pivots[i]] = a[i][m];
  return optional(pair(move(c), ker_basis(a, pivots, rank)));
}
