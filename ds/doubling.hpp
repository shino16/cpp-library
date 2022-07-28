#pragma once
#include "bit/ilog2.hpp"
#include "bit/ctz.hpp"

class doubling {
 public:
  template <class Iter>
  doubling(Iter f, Iter l, ll max_power = LONG_LONG_MAX)
      : size(l - f), height(ilog2(max_power) + 1), data(height) {
    data[0].assign(f, l);
    rep(h, height - 1) {
      data[h + 1].resize(size);
      rep(x, size) data[h + 1][x] = data[h][data[h][x]];
    }
  }
  template <class Iter>
  doubling(Iter f, Iter l) : doubling(f, l, l - f) {}

  int apply(ll power, int x) const {
    rep(h, height) if (power >> h & 1) x = data[h][x];
    return x;
  }
  int operator()(ll power, int x) const { return apply(power, x); }

 private:
  int size, height;
  vector<vector<int>> data;
};