#pragma once
#include "bit/ilog2.hpp"
#include "bit/ctz.hpp"

class doubling {
 public:
  template <class Iter>
  doubling(Iter f, Iter l, int max_power)
      : size(l - f), height(ilog2(max_power) + 1), data(height) {
    data[0].assign(f, l);
    rep(h, height - 1) {
      data[h + 1].resize(size);
      rep(x, size) data[h + 1][x] = data[h][data[h][x]];
    }
  }
  template <class Iter>
  doubling(Iter f, Iter l) : doubling(f, l, l - f) {}

  int apply(int power, int x) const {
    while (power) {
      int h = ctz(power);
      x = data[h][x];
      power ^= 1 << h;
    }
    return x;
  }
  int operator()(int power, int x) const { return apply(power, x); }

 private:
  int size, height;
  vector<vector<int>> data;
};