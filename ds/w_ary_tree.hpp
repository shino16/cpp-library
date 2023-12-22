#pragma once
#include "bit/clz.hpp"
#include "bit/ctz.hpp"

template <class T0, make_unsigned_t<T0> U, class = void>
class w_ary_tree {
  using T = make_unsigned_t<T0>;
 public:
  bool insert(T x) {
    if (!ptr) ptr = make_unique<w_ary_tree<T0, V>[]>((U - 1) / V + 1);
    mask |= uint64_t(1) << (x / V);
    return ptr[x / V].insert(x % V);
  }
  bool erase(T x) {
    if (!ptr) return false;
    bool ret = ptr[x / V].erase(x % V);
    if (ptr[x / V].mask == 0) {
      if constexpr (V > 64) ptr[x / V].ptr.reset();
      mask &= ~(uint64_t(1) << (x / V));
    }
    return ret;
  }
  bool contains(T x) const { return ptr && ptr[x / V].contains(x % V); }
  T min() const {
    if (!mask) return -1;
    T i = ctz(mask);
    return (i * V) | ptr[i].min();
  }
  T max() const {
    if (!mask) return -1;
    T i = 63 - clz(mask);
    return (i * V) | ptr[i].max();
  }
  // max s s.t. s < x
  T pred(T x) const {
    if (!ptr) return -1;
    T u = ptr[x / V].pred(x % V);
    if (u != -1) return (x & -V) | u;
    uint64_t mask2 = mask & ~(~uint64_t(0) << (x / V));
    if (mask2 == 0) return -1;
    int i = 63 - clz(mask2);
    return (i * V) | ptr[i].max();
  }
  // min s s.t. s >= x
  T succ(T x) const {
    if (!ptr) return -1;
    T u = ptr[x / V].succ(x % V);
    if (u != -1) return (x & -V) | u;
    uint64_t mask2 = mask & ~(~uint64_t(0) >> (63 - x / V));
    if (mask2 == 0) return -1;
    int i = ctz(mask2);
    return (i * V) | ptr[i].min();
  }

 private:
  static constexpr T calc_v(T u) {
    T res = 1;
    while (u > 64) u /= 64, res *= 64;
    return res;
  }
  static constexpr T V = calc_v(U);
  uint64_t mask = 0;
  unique_ptr<w_ary_tree<T0, V>[]> ptr;
  template <class T2, make_unsigned_t<T2>, class>
  friend class w_ary_tree;
};

template <class T0, make_unsigned_t<T0> U>
class w_ary_tree<T0, U, enable_if_t<U <= 64>> {
  using T = make_unsigned_t<T0>;
 public:
  bool insert(T x) {
    bool ret = ~mask >> x & 1;
    mask |= uint64_t(1) << x;
    return ret;
  }
  bool erase(T x) {
    bool ret = mask >> x & 1;
    mask &= ~(uint64_t(1) << x);
    return ret;
  }
  bool contains(T x) const { return mask >> x & 1; }
  T min() const { return mask ? ctz(mask) : -1; }
  T max() const { return mask ? 63 - clz(mask) : -1; }
  // max s s.t. s < x
  T pred(T x) const {
    uint64_t mask2 = mask & ~(~uint64_t(0) << x);
    return mask2 == 0 ? -1 : 63 - clz(mask2);
  }
  T succ(T x) const {
    uint64_t mask2 = mask & (~uint64_t(0) << x);
    return mask2 == 0 ? -1 : ctz(mask2);
  }

 private:
  uint64_t mask = 0;
  template <class T2, make_unsigned_t<T2>, class>
  friend class w_ary_tree;
};
