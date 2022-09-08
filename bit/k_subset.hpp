#pragma once
#include "bit/ctz.hpp"

template <class F>
void k_subset(int n, int k, F f = F()) {
  if (k == 0) return f(0), void();
  for (int mask = (1 << k) - 1; mask < 1 << n;) {
    f(mask);
    int lsb = mask & -mask;
    mask += lsb;
    int d = ctz(mask) - ctz(lsb) - 1;
    mask |= (1 << d) - 1;
  }
}
