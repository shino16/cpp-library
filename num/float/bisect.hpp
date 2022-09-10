#pragma once
#include "prelude.hpp"

template <class F>
double bisect(double l, double r, double e, F p) {
  int k = log2((r - l) / e) + 2;
  rep(i, k) {
    double m = (l + r) / 2;
    (p(m) ? l : r) = m;
  }
  return l;
}