#pragma once
#include "algebra.hpp"

template <class M>
class segment_tree {
 public:
  using value_type = typename M::type;
  template <class Iter>
  segment_tree(Iter f, Iter l, M m = M()) : m(m), data((l - f) * 2) {
    copy(f, l, data.begin() + (l - f));
    init();
  }
  template <class F>
  segment_tree(int n, F f, M m = M()) : m(m), data(n * 2) {
    rep(i, n) data[i + n] = f(i);
    init();
  }
  segment_tree(int n = 0, M m = M()) : m(m), data(n * 2, m.unit()) {}

  int size() const { return data.size() / 2; }
  value_type prod(int l, int r) const {
    value_type accl = m.unit(), accr = m.unit();
    for (l += size(), r += size(); l < r; l >>= 1, r >>= 1) {
      if (l & 1) accl = m.op(accl, data[l++]);
      if (r & 1) accr = m.op(data[--r], accr);
    }
    return m.op(accl, accr);
  }
  void add(int i, value_type v) {
    exec(i, [=](value_type& e) { e = m.op(e, v); });
  }
  void set(int i, value_type v) {
    exec(i, [=](value_type& e) { e = v; });
  }
  template <class F>
  void exec(int i, F f) {
    f(data[i + size()]);
    for (i += size(); i >>= 1;) data[i] = m.op(data[i << 1], data[i << 1 | 1]);
  }

 private:
  M m;
  vector<value_type> data;

  void init() {
    repr2(i, 1, size()) data[i] = m.op(data[i << 1], data[i << 1 | 1]);
  }
};
