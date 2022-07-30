#pragma once
#include "algebra.hpp"

template <class M>
class sparse_table {
 public:
  using value_type = typename M::type;
  sparse_table(vector<value_type> v, M m = M()) : m(m), data({move(v)}) {
    int n = data[0].size();
    lg.resize(n + 1);
    rep2(i, 2, n + 1) lg[i] = lg[i / 2] + 1;
    data.resize(lg[n] + 1);
    rep(t, lg[n]) {
      int w = 1 << t;
      data[t + 1].resize(n - w * 2 + 1);
      rep(i, n - w * 2 + 1) data[t + 1][i] = m.op(data[t][i], data[t][i + w]);
    }
  }
  template <class It>
  sparse_table(It first, It last, M m = M()) : sparse_table({first, last}, m) {}

  value_type prod(int l, int r) {
    if (l == r) return m.unit();
    int t = lg[r - l];
    return m.op(data[t][l], data[t][r - (1 << t)]);
  }
  value_type disjoint_prod(int l, int r) {
    value_type res = m.unit();
    while (l != r) {
      int t = lg[r - l];
      res = m.op(res, data[t][l]);
      l += 1 << t;
    }
    return res;
  }

 private:
  M m;
  vector<vector<value_type>> data;
  vector<int> lg;
};
