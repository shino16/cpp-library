#pragma once
#include "prelude.hpp"

template <class Iter>
auto decompose(Iter first, Iter last) -> vector<vector<int>> {
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
