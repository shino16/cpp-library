#pragma once
#include "prelude.hpp"

// (min f, argmin f)
template <class F>
auto convex_min(double l, double r, double e, const F& f)
    -> pair<decltype(f(0.0)), double> {
  const double PHI = 1.618033988749895;
  int k = log((r - l) / e) / log(PHI) + 2;
  double ml = (PHI * l + r) / (PHI + 1); auto yml = f(ml);
  double mr = (l + PHI * r) / (PHI + 1); auto ymr = f(mr);
  for (int i = 0; i < k; i++) {
    if (yml > ymr) {
      l = ml;
      ml = mr; yml = ymr;
      mr = (ml + PHI * r) / (1.0 + PHI); ymr = f(mr);
    } else {
      r = mr;
      mr = ml; ymr = yml;
      ml = (PHI * l + mr) / (1.0 + PHI); yml = f(ml);
    }
  }
  return pair(yml, ml);
}
