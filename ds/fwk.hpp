#pragma once
#include "alg.hpp"
#include "prelude.hpp"

template <class M>
class fenwick_tree {
 public:
  using value_type = typename M::type;
  fenwick_tree(vector<value_type> data, M m = M()) : m(m), data(move(data)) {
    data.insert(data.cbegin(), m.unit());
    for (int i = 1; i < data.size(); i++) {
      if (i + lsb(i) < data.size())
        data[i + lsb(i)] = m.op(data[i + lsb(i)], data[i]);
    }
  }
  fenwick_tree(int n = 0, M m = M())
      : fenwick_tree(vector<value_type>(n, m.unit()), m) {}
  int size() const { return data.size() - 1; }
  void clear() { fill(data.begin(), data.end(), m.unit()); }
  void add(int i, value_type v) {
    for (i++; i < data.size(); i += lsb(i)) data[i] = m.op(data[i], v);
  }
  void sub(int i, value_type v) { add(i, m.inv(v)); }
  value_type sum(int r) const {
    value_type res = m.unit();
    for (; r; r -= lsb(r)) res = m.op(res, data[r]);
    return res;
  }
  value_type sum(int l, int r) const { return m.op(m.inv(sum(l)), sum(r)); }
  template <class F>
  int lower_bound(F pred = F()) const {
    int i = 0;
    value_type acc = m.unit();
    if (!pred(acc)) return i;
    for (int w = bit_ceil(data.size()); w >>= 1;) {
      if (i + w < data.size()) {
        value_type acc2 = m.op(acc, data[i + w]);
        if (pred(acc2)) i += w, acc = acc2;
      }
    }
    return i + 1;
  }

 private:
  M m;
  vector<value_type> data;
  static int lsb(int a) { return a & -a; }
};