#pragma once
#include "prelude.hpp"

template <class T>
class potential_dsu {
 public:
  potential_dsu(int n) : par(n, -1), f(n), cnt(n) {}
  int count() const { return cnt; }
  void clear() {
    fill(par.begin(), par.end(), -1);
    cnt = par.size();
  }
  int find(int x) {
    if (par[x] < 0) return x;
    int r = find(par[x]);
    f[x] += f[par[x]];
    return par[x] = r;
  }
  bool same(int x, int y) { return find(x) == find(y); }
  T phi(int x) { return find(x), f[x]; }
  // phi(x) + d = phi(y)
  // Returns false on failure
  bool unite(int x, int y, T d) {
    d += phi(x), x = find(x);
    d -= phi(y), y = find(y);
    if (x == y) return d != T(0);
    if (par[x] > par[y]) swap(x, y), d = -d;
    par[x] += par[y], par[y] = x, f[y] = d;
    cnt--;
    return false;
  }
  int size(int x) { return -par[find(x)]; }
  vector<vector<int>> groups() {
    vector<vector<int>> res(par.size());
    for (int x = 0; x < par.size(); x++) res[find(x)].push_back(x);
    res.erase(remove_if(all(res), [](const auto& v) { return v.empty(); }),
              res.end());
    return res;
  }

 private:
  vector<int> par;
  vector<T> f;  // f(x) - f(par(x))
  int cnt;
};
