#pragma once
#include "util/seed.hpp"

class rolling_hash {
 public:
  uint64_t r;
  static constexpr uint64_t MOD = (uint64_t(1) << 61) - 1;

  template <class It>
  rolling_hash(It first, It last, uint64_t r)
      : r(r), prefix(last - first + 1), power(last - first + 1) {
    prefix[0] = 0;
    power[0] = 1;
    rep(i, last - first) {
      prefix[i + 1] = reduce(mul(prefix[i], r) + uint64_t(first[i]));
      power[i + 1] = mul(power[i], r);
    }
  }
  template <class It>
  rolling_hash(It first, It last) : rolling_hash(first, last, seed()) {}

  uint64_t operator()(int l, int r) const {
    uint64_t t = prefix[r] + MOD - mul(power[r - l], prefix[l]);
    return reduce(t);
  }
  template <class It>
  uint64_t operator()(It first, It last) const {
    uint64_t t = 0;
    for (auto it = first; it != last; it++) t = reduce(mul(t, r) + *it);
    return t;
  }

 private:
  vector<uint64_t> prefix, power;
  static uint64_t mul(uint64_t a, uint64_t b) {
    __uint128_t t = __uint128_t(a) * b;
    return reduce((t >> 61) + (t & MOD));
  }
  // [0, 2 * MOD) -> [0, MOD)
  static uint64_t reduce(uint64_t a) { return a >= MOD ? a - MOD : a; }
};
