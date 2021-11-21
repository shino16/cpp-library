#pragma once
#include "alg.hpp"
#include "bit/ctz.hpp"
#include "bit/ilog2.hpp"
#include "prelude.hpp"

template <class M, class A, class Act>
class lazy_segment_tree {
 public:
  using value_type = typename M::type;
  using actor_type = typename A::type;
  template <class Iter>
  lazy_segment_tree(Iter first, Iter last, M m = M(), A a = A(), Act f = Act())
      : m(m), a(a), f(f), data((last - first) * 2), lazy(last - first, a.unit()) {
    copy(first, last, data.begin() + (last - first));
    init();
  }
  lazy_segment_tree(const vector<value_type>& data, M m = M(), A a = A(),
                    Act f = Act())
      : lazy_segment_tree(all(data), m, a, f) {}
  lazy_segment_tree(int n = 0, M m = M(), A a = A(), Act f = Act())
      : m(m), a(a), f(f), data(n * 2, m.unit()), lazy(n, a.unit()) {}
  void init() {
    for (int i = size(); --i;) data[i] = m.op(data[i << 1], data[i << 1 | 1]);
  }
  int size() const { return data.size() / 2; }
  value_type prod(int l, int r) {
    flush(trunc(l + size()));
    flush(trunc(r + size()) - 1);
    value_type accl = m.unit(), accr = m.unit();
    for (l += size(), r += size(); l < r; l >>= 1, r >>= 1) {
      if (l & 1) accl = m.op(accl, data[l++]);
      if (r & 1) accr = m.op(data[--r], accr);
    }
    return m.op(accl, accr);
  }
  void act(int l, int r, actor_type x) {
    if (x == a.unit()) return;
    flush(trunc(l + size()));
    flush(trunc(r + size()) - 1);
    for (int L = l + size(), R = r + size(); L < R; L >>= 1, R >>= 1) {
      if (L & 1) apply(L++, x);
      if (R & 1) apply(--R, x);
    }
    build(trunc(l + size()));
    build(trunc(r + size()) - 1);
  }
  void add(int i, value_type v) { exec(i, [=](value_type& e) { e = m.op(e, v); }); }
  void set(int i, value_type v) { exec(i, [=](value_type& e) { e = move(v); }); }
  template <class F>
  void exec(int i, F f) {
    flush(trunc(i + size()));
    f(data[i + size()]);
    build(trunc(i + size()));
  }

 private:
  M m;
  A a;
  Act f;
  vector<value_type> data;
  vector<actor_type> lazy;
  static int trunc(int a) { return a >> ctz(a); }
  void apply(int i, actor_type x) {
    data[i] = f(data[i], x);
    if (i < size()) lazy[i] = a.op(lazy[i], x);
  }
  void push(int i) {
    if (lazy[i] != a.unit()) {
      apply(i << 1, lazy[i]);
      apply(i << 1 | 1, lazy[i]);
      lazy[i] = a.unit();
    }
  }
  void upd(int i) { data[i] = m.op(data[i << 1], data[i << 1 | 1]); }
  void flush(int i) { if (i) for (int s = ilog2(i); s > 0; s--) push(i >> s); }
  void build(int i) { for (; i >>= 1;) upd(i); }
};
