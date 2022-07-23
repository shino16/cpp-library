#pragma once
#include "prelude.hpp"

template <class It>
vector<vector<int>> cycles(It first, It last) {
  int n = last - first;
  vector<int> from(n, -1);
  vector<vector<int>> res;
  rep(s, n) if (from[s] == -1) {
    int v = s;
    for (; from[v] == -1; v = first[v]) from[v] = s;
    if (from[v] == s) {
      vector<int> c = {v};
      for (v = first[v]; v != c[0]; v = first[v]) c.push_back(v);
      res.push_back(move(c));
    }
  }
  return res;
}
