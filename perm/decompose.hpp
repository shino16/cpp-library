#pragma once
#include "prelude.hpp"

template <class Iter>
vector<vector<int>> decompose(Iter first, Iter last) {
  int n = last - first;
  vector<bool> done(n, false);
  vector<vector<int>> ans;
  rep(i, n) if (!done[i]) {
    vector<int> now = {i};
    for (int v = first[i]; v != i; v = first[v]) done[v] = true, now.push_back(v);
    ans.push_back(move(now));
  }
  return ans;
}
