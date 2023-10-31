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
  void mul(int i, value_type v) {
    exec(i, [&](value_type& e) { e = m.op(e, v); });
  }
  void set(int i, value_type v) {
    exec(i, [&](value_type& e) { e = v; });
  }
  template <class F>
  void exec(int i, F f) {
    f(data[i + size()]);
    for (i += size(); i >>= 1;) data[i] = m.op(data[i << 1], data[i << 1 | 1]);
  }
  // min r s.t. !f(prod(l, r)) or size()+1 if no such r exists
  template <class F>
  int partition_point(int l, F f) const {
    if (!f(m.unit())) return l;
    if (f(data[1])) return size() + 1;
    if (l < size() && !f(data[l + size()])) return l + 1;
    int r = l + size();
    while (r % 2 == 0) r /= 2;
    value_type acc = m.unit();
    do {
      value_type acc2 = m.op(acc, data[r]);
      if (f(acc2)) {
        acc = acc2, r++;
        while (r % 2 == 0) r /= 2;
      } else if (r < size()) {
        r *= 2;
      }
    } while (r < size());
    if (f(m.op(acc, data[r]))) r++;
    r = r + 1 - size();
    return r <= l ? size() + 1 : r;
  }
  // max l s.t. !f(prod(l, r)) or -1 if no such l exists
  template <class F>
  int rpartition_point(int r, F f) const {
    if (!f(m.unit())) return r;
    if (f(data[1])) return -1;
    if (r > 0 && !f(data[r - 1 + size()])) return r - 1;
    int l = r + size() - 1;
    while (l % 2 == 1 && l > 1) l /= 2;
    value_type acc = m.unit();
    do {
      value_type acc2 = m.op(data[l], acc);
      if (f(acc2)) {
        acc = acc2, l--;
        while (l % 2 == 1 && l > 1) l /= 2;
      } else if (l < size()) {
        l = l * 2 + 1;
      }
    } while (l < size());
    if (f(m.op(data[l], acc))) l--;
    l = l - size();
    return l >= r ? -1 : l;
  }
  // min r s.t. prod(l, r) >= x
  template <class Comp = less<>>
  int lower_bound(int l, value_type x, Comp comp = Comp()) const {
    return partition_point(l, [&](auto y) { return comp(y, x); });
  }
  // max l s.t. prod(l, r) >= x
  template <class Comp = less<>>
  int rlower_bound(int r, value_type x, Comp comp = Comp()) const {
    return rpartition_point(r, [&](auto y) { return comp(y, x); });
  }

 private:
  M m;
  vector<value_type> data;

  void init() {
    repr2(i, 1, size()) data[i] = m.op(data[i << 1], data[i << 1 | 1]);
  }
};
