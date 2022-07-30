#pragma once
#include "bit/popcnt.hpp"
#include "prelude.hpp"

class bit_vector {
 public:
  bit_vector(int n = 0) : bit(n / 8 + 1), sum(n / 8 + 2) {}
  template <class It>
  bit_vector(It a, It a_last) : bit_vector(a_last - a) {
    int n = a_last - a;
    rep(i, n) bit[i / 64] |= uint64_t(a[i] != 0) << (i % 64);
    rep(i, bit.size()) sum[i + 1] = sum[i] + popcnt(bit[i]);
  }
  int size() const { return bit.size() * 64; }
  bool operator[](int i) const { return bit[i / 64] >> (i % 64) & 1; }
  int rank0(int r) const { return r - rank1(r); }
  int rank0(int l, int r) const { return rank0(r) - rank0(l); }
  int rank1(int r) const {
    return sum[r / 64] + popcnt(bit[r / 64] & ~(~uint64_t(0) << (r % 64)));
  }
  int rank1(int l, int r) const { return rank1(r) - rank1(l); }
  int rank(bool b, int r) const { return b ? rank1(r) : rank0(r); }
  int rank(bool b, int l, int r) const { return b ? rank1(l, r) : rank0(l, r); }
  int select0(int l, int k) const {
    int r = bit.size() * 8;
    while (l + 1 < r) {
      int m = (l + r) / 2;
      (rank0(m) <= k ? l : r) = m;
    }
    return l;
  }
  int select0(int k) const { return select0(0, k); }
  int select1(int l, int k) const {
    int r = bit.size() * 8;
    while (l + 1 < r) {
      int m = (l + r) / 2;
      (rank1(m) <= k ? l : r) = m;
    }
    return l;
  }
  int select1(int k) const { return select1(0, k); }
  int select(bool v, int k) const { return v ? select1(k) : select0(k); }
  int select(bool v, int l, int k) const {
    return v ? select1(l, k) : select0(l, k);
  }

 private:
  vector<uint64_t> bit;
  vector<int> sum;
};
