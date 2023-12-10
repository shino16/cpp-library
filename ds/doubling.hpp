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

  int apply(ll power, int x) const {
    rep(h, height) if (power >> h & 1) x = data[h][x];
    return x;
  }
  int operator()(ll power, int x) const { return apply(power, x); }
  // min i s.t. !p(apply(i, x))
  template <class P>
  int partition_point(int x, P p) const {
    if (!p(x)) return 0;
    int i = 0;
    repr(h, height)
      if (p(data[h][x])) i |= 1 << h, x = data[h][x];
    return i + 1;
  }

 private:
  int size, height;
  vector<vector<int>> data;
};
