#pragma once
#include "ds/segtree.hpp"

template <class M>
class segment_tree_binsearch : public segment_tree<M> {
 public:
  using segment_tree<M>::segment_tree;
  using value_type = segment_tree<M>::value_type;

  // min r s.t. !f(prod(l, r)) or size()+1 if no such r exists
  template <class F>
  int partition_point(int l, F f) const {
    if (!f(this->m.unit())) return l;
    if (f(this->data[1])) return this->size() + 1;
    if (l < this->size() && !f(this->data[l + this->size()])) return l + 1;
    int r = l + this->size();
    while (r % 2 == 0) r /= 2;
    value_type acc = this->m.unit();
    do {
      value_type acc2 = this->m.op(acc, this->data[r]);
      if (f(acc2)) {
        acc = acc2, r++;
        while (r % 2 == 0) r /= 2;
      } else if (r < this->size()) {
        r *= 2;
      }
    } while (r < this->size());
    if (f(this->m.op(acc, this->data[r]))) r++;
    r = r + 1 - this->size();
    return r <= l ? this->size() + 1 : r;
  }

  // max l s.t. !f(prod(l, r)) or -1 if no such l exists
  template <class F>
  int rpartition_point(int r, F f) const {
    if (!f(this->m.unit())) return r;
    if (f(this->data[1])) return -1;
    if (r > 0 && !f(this->data[r - 1 + this->size()])) return r - 1;
    int l = r + this->size() - 1;
    while (l % 2 == 1 && l > 1) l /= 2;
    value_type acc = this->m.unit();
    do {
      value_type acc2 = this->m.op(this->data[l], acc);
      if (f(acc2)) {
        acc = acc2, l--;
        while (l % 2 == 1 && l > 1) l /= 2;
      } else if (l < this->size()) {
        l = l * 2 + 1;
      }
    } while (l < this->size());
    if (f(this->m.op(this->data[l], acc))) l--;
    l = l - this->size();
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
};
