#pragma once

#include "prelude.hpp"
#include "mod/fact.hpp"

// Returns f(x) given deg(f) < ys.size(), f(i + x_base) == ys[i]
template <class Y, class X>
Y interpolate_iota(const vector<Y>& ys, X x, X x_base = 0) {
  int n = ys.size();
  vector<Y> cumprod(n);
  cumprod[0] = 1;
  rep(i, n-1) cumprod[i+1] = cumprod[i] * (x - (x_base + i));
  Y prod_r = 1;
  Y ans = 0;
  repr(i, n) {
    Y d = ys[i] * cumprod[i] * prod_r * inv_fact<Y>(i) * inv_fact<Y>(n-i-1);
    ans += d * ((n - i - 1) % 2 ? -1 : 1);
    prod_r *= x - (x_base + i);
  }
  return ans;
}
