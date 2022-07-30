#pragma once
#include "algebra.hpp"
#include "bit/ctz.hpp"
#include "bit/ilog2.hpp"

template <class T, class A, class F>
class dual_segment_tree {
 public:
  using value_type = T;
  using actor_type = typename A::type;
  dual_segment_tree(vector<value_type> v, A a = A(), F f = F())
      : a(a), f(f), data(move(v)), lazy(data.size(), a.unit()) {}
  template <class Iter>
  dual_segment_tree(Iter first, Iter last, A a = A(), F f = F())
      : dual_segment_tree({first, last}, a, f) {}
  dual_segment_tree(int n = 0, T e = T(), A a = A(), F f = F())
      : a(a), f(f), data(n, e), lazy(n, a.unit()) {}

  int size() const { return data.size(); }
  value_type get(int i) {
    flush(i + size());
    return data[i];
  }
  void apply(int l, int r, actor_type x) {
    if (x == a.unit()) return;
    flush(trunc(l + size()));
    flush(trunc(r + size()) - 1);
    for (int L = l + size(), R = r + size(); L < R; L >>= 1, R >>= 1) {
      if (L & 1) apply(L++, x);
      if (R & 1) apply(--R, x);
    }
  }
  void add(int i, value_type v) {
    exec(i, [=](value_type& e) { e = e.op(e, v); });
  }
  void set(int i, value_type v) {
    exec(i, [=](value_type& e) { e = v; });
  }
  template <class G>
  void exec(int i, G f) {
    flush(trunc(i + size()));
    f(data[i]);
  }

 private:
  A a;
  F f;
  vector<value_type> data;
  vector<actor_type> lazy;
  static int trunc(int a) { return a >> ctz(a); }
  void apply(int i, actor_type x) {
    if (i < size())
      lazy[i] = a.op(lazy[i], x);
    else
      data[i - size()] = f(data[i - size()], x);
  }
  void push(int i) {
    if (lazy[i] != a.unit()) {
      apply(i << 1, lazy[i]);
      apply(i << 1 | 1, lazy[i]);
      lazy[i] = a.unit();
    }
  }
  void flush(int i) {
    if (i)
      for (int s = ilog2(i); s > 0; s--) push(i >> s);
  }
};
