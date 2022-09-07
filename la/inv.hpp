#pragma once
#include "la/row_reduce.hpp"

// Return true on failure
template <class T>
bool invert(vector<vector<T>>& a) {
  int n = a.size();
  assert(a[0].size() == n);
  rep(i, n) a[i].insert(a[i].end(), n, T(0)), a[i][n + i]++;
  int r = row_reduce(a).second;
  if (r != n) return true;
  rep(i, n) a[i].erase(a[i].begin(), a[i].begin() + n);
  return false;
}
