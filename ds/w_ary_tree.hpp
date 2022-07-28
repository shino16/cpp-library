#pragma once
#include "bit/clz.hpp"
#include "bit/ctz.hpp"

template <uint64_t U, class = void>
class w_ary_tree {
 public:
  bool insert(uint64_t x) {
    if (!ptr) ptr = make_unique<w_ary_tree<V>[]>((U - 1) / V + 1);
    mask |= uint64_t(1) << (x / V);
    return ptr[x / V].insert(x % V);
  }
  bool erase(uint64_t x) {
    if (~mask >> (x / V) & 1) return false;
    bool ret = ptr[x / V].erase(x % V);
    if (ptr[x / V].mask == 0) {
      if constexpr (V > 64) ptr[x / V].ptr.reset();
      mask &= ~(uint64_t(1) << (x / V));
    }
    return ret;
  }
  bool contains(uint64_t x) const { return ptr && ptr[x / V].contains(x % V); }
  uint64_t min() const {
    uint64_t i = ctz(mask);
    return (i * V) | ptr[i].min();
  }
  uint64_t max() const {
    uint64_t i = 63 - clz(mask);
    return (i * V) | ptr[i].max();
  }
  // max s s.t. s < x
  uint64_t pred(uint64_t x) const {
    if (!ptr) return -1;
    uint64_t u = ptr[x / V].pred(x % V);
    if (u != -1) return (x & -V) | u;
    uint64_t mask2 = mask & ~(~uint64_t(0) << (x / V));
    if (mask2 == 0) return -1;
    int i = 63 - clz(mask2);
    return (i * V) | ptr[i].max();
  }
  // min s s.t. s >= x
  uint64_t succ(uint64_t x) const {
    if (!ptr) return -1;
    uint64_t u = ptr[x / V].succ(x % V);
    if (u != -1) return (x & -V) | u;
    uint64_t mask2 = mask & ~(~uint64_t(0) >> (63 - x / V));
    if (mask2 == 0) return -1;
    int i = ctz(mask2);
    return (i * V) | ptr[i].min();
  }

 private:
  static constexpr uint64_t calc_v(uint64_t u) {
    uint64_t res = 1;
    while (u > 64) u /= 64, res *= 64;
    return res;
  }
  static constexpr uint64_t V = calc_v(U);
  uint64_t mask = 0;
  unique_ptr<w_ary_tree<V>[]> ptr;
  template <uint64_t, class>
  friend class w_ary_tree;
};

template <uint64_t U>
class w_ary_tree<U, enable_if_t<U <= 64>> {
 public:
  bool insert(uint64_t x) {
    bool ret = ~mask >> x & 1;
    mask |= uint64_t(1) << x;
    return ret;
  }
  bool erase(uint64_t x) {
    bool ret = mask >> x & 1;
    mask &= ~(uint64_t(1) << x);
    return ret;
  }
  bool contains(uint64_t x) const { return mask >> x & 1; }
  uint64_t min() const { return ctz(mask); }
  uint64_t max() const { return 63 - clz(mask); }
  // max s s.t. s < x
  uint64_t pred(uint64_t x) const {
    uint64_t mask2 = mask & ~(~uint64_t(0) << x);
    return mask2 == 0 ? -1 : 63 - clz(mask2);
  }
  uint64_t succ(uint64_t x) const {
    uint64_t mask2 = mask & (~uint64_t(0) << x);
    return mask2 == 0 ? -1 : ctz(mask2);
  }

 private:
  uint64_t mask = 0;
  template <uint64_t, class>
  friend class w_ary_tree;
};
