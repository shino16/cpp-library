#pragma once
#include "ds/fenwick.hpp"

template <class M, class F>
class range_fenwick_tree {
 public:
  using value_type = typename M::type;
  range_fenwick_tree(vector<value_type> data, M m = M(), F mul = F())
      : m(m), mul(mul), rect(move(data), m), tri(data.size(), m) {}
  range_fenwick_tree(int n = 0, M m = M(), F mul = F())
      : m(m), mul(mul), rect(n, m), tri(n, m) {}
  int size() const { return rect.size(); }
  void clear() { rect.clear(), tri.clear(); }
  void add(int i, value_type v) { rect.add(i, v); }
  void add(int l, int r, value_type v) {
    tri.add(l, v), tri.sub(r, v);
    rect.sub(l, mul(v, l)), rect.add(r, mul(v, r));
  }
  void sub(int i, value_type v) { add(i, m.inv(v)); }
  void sub(int l, int r, value_type v) { add(l, r, m.inv(v)); }
  value_type sum(int r) const { return m.op(rect.sum(r), mul(tri.sum(r), r)); }
  value_type sum(int l, int r) const { return m.op(m.inv(sum(l)), sum(r)); }
  // template <class F>
  // int partition_point(F pred = F()) const {
  //   int i = 0;
  //   value_type s = m.unit();
  //   if (!pred(s)) return i;
  //   for (int w = bit_floor(rect.data.size()); w; w >>= 1) {
  //     if (i + w < rect.data.size()) {
  //       value_type s2 =
  //           m.op(m.op(s, rect.data[i + w]), mul(tri.data[i + w], i + w + 1));
  //       if (pred(s2)) i += w, s = s2;
  //     }
  //   }
  //   return i + 1;
  // }
  // // min i s.t. !comp(sum(i), x)
  // template <class Comp = less<value_type>>
  // int lower_bound(value_type x, Comp comp = Comp()) const {
  //   return partition_point([&](value_type s) { return comp(s, x); });
  // }

 private:
  M m;
  F mul;
  fenwick_tree<M> rect, tri;
};