#pragma once
#include "prelude.hpp"

// returns (min f, argmin f)
template <class F>
auto convex_min(double l, double r, double e, F f) {
  const double PHI = 1.6180339887498948;
  int k = log((r - l) / e) / log(PHI) + 2;
  double x = (PHI * l + r) / (1 + PHI);
  double y = (l + PHI * r) / (1 + PHI);
  double fx = f(x);
  double fy = f(y);
  rep(i, k) {
    if (fx < fy) {
      l = x;
      tie(x, fx) = make_pair(y, fy);
      y = (l + PHI * r) / (1 + PHI);
      fy = f(y);
    } else {
      r = y;
      tie(y, fy) = make_pair(x, fx);
      x = (PHI * l + r) / (1 + PHI);
      fx = f(x);
    }
  }
  return make_pair(f(x), x);
}
