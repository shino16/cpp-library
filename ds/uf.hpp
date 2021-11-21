#pragma once
#include "prelude.hpp"

class union_find {
 public:
  union_find(int n) : par(n, -1) {}
  int size() const { return par.size(); }
  int count() const { return count_; }
  void clear() {
    fill(par.begin(), par.end(), -1);
    count_ = size();
  }
  int find(int x) { return par[x] < 0 ? x : par[x] = (int)find(par[x]); }
  bool same(int x, int y) { return find(x) == find(y); }
  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y], par[y] = (int)x;
    count_--;
    return true;
  }
  vector<vector<int>> groups() {
    vector<vector<int>> res(size());
    for (int x = 0; x < size(); x++) res[find(x)].push_back(x);
    res.erase(remove_if(all(res), [](const auto& v) { return v.empty(); }),
              res.end());
    return res;
  }

 private:
  vector<int> par;
  int count_;
};