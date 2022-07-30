#pragma once
#include "algebra.hpp"
#include "bit/ilog2.hpp"

template <class M>
class fenwick_tree {
 public:
  using value_type = typename M::type;
  fenwick_tree(vector<value_type> v, M m = M()) : m(m), data(move(v)) {
    data.insert(data.cbegin(), m.unit());
    for (int i = 1; i < data.size(); i++) {
      if (i + lsb(i) < data.size())
        data[i + lsb(i)] = m.op(data[i + lsb(i)], data[i]);
    }
  }
  template <class Iter>
  fenwick_tree(Iter f, Iter l, M m = M())
      : fenwick_tree(vector<value_type>(f, l), m) {}
  fenwick_tree(int n, M m = M()) : m(m), data(n + 1, m.unit()) {}
  int size() const { return data.size() - 1; }
  void clear() { fill(data.begin(), data.end(), m.unit()); }
  void add(int i, value_type v) {
    for (i++; i < data.size(); i += lsb(i)) data[i] = m.op(data[i], v);
  }
  void sub(int i, value_type v) { add(i, m.inv(v)); }
  void assign(int i, value_type v) { add(i, m.op(v, m.inv(sum(i, i + 1)))); }
  value_type sum(int r) const {
    value_type res = m.unit();
    for (; r; r -= lsb(r)) res = m.op(res, data[r]);
    return res;
  }
  value_type sum(int l, int r) const { return m.op(m.inv(sum(l)), sum(r)); }
  template <class F>
  int partition_point(F pred = F()) const {
    int i = 0;
    value_type s = m.unit();
    if (!pred(s)) return i;
    for (int w = bit_floor(data.size()); w; w >>= 1) {
      if (i + w < data.size()) {
        value_type s2 = m.op(s, data[i + w]);
        if (pred(s2)) i += w, s = s2;
      }
    }
    return i + 1;
  }
  // min i s.t. !comp(sum(i), x)
  template <class Comp = less<value_type>>
  int lower_bound(value_type x, Comp comp = Comp()) const {
    return partition_point([&](value_type s) { return comp(s, x); });
  }

 private:
  M m;
  vector<value_type> data;
  static int lsb(int a) { return a & -a; }
};