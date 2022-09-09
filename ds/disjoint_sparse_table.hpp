#pragma once
#include "algebra.hpp"
#include "bit/clz.hpp"

template <class M>
class disjoint_sparse_table {
 public:
  using value_type = typename M::type;
  template <class It>
  disjoint_sparse_table(It a, It last, M m = M()) : m(m) {
    int n = last - a;
    data.emplace_back(a, last);
    int w = 2;
    while (w < n) {
      vector<value_type> row(n, m.unit());
      int j = 0;
      for (; j + w * 2 < n; j += w * 2) {
        value_type prod = m.unit();
        repr2(i, j, j + w) row[i] = prod = m.op(a[i], prod);
        prod = m.unit();
        rep2(i, j + w, j + w * 2) row[i] = prod = m.op(prod, a[i]);
      }
      if (j + w < n) {
        value_type prod = m.unit();
        repr2(i, j, j + w) row[i] = prod = m.op(a[i], prod);
        prod = m.unit();
        rep2(i, j + w, n) row[i] = prod = m.op(prod, a[i]);
      }
      data.push_back(move(row));
      w *= 2;
    }
  }

  value_type prod(int l, int r) {
    if (l == r) return m.unit();
    if (l + 1 == r) return data[0][l];
    int i = 31 - clz(l ^ (r - 1));
    return m.op(data[i][l], data[i][r - 1]);
  }

 private:
  M m;
  vector<vector<value_type>> data;
};
