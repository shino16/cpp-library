#pragma once
#include "prelude.hpp"

// Returns (r, s) with |r| < N, s > 0, r/s = x (mod M)
template <class mint>
pair<int, int> to_ratio(mint x, int N = 22341) {
  int r = x.val(), t = mint::mod();
  int s = 1, u = 0;
  // r - sx - My = 0
  // t - ux - Mz = 0
  while (r >= N) {
    int q = r / t;
    swap(r -= q * t, t);
    swap(s -= q * u, u);
  }
  if (s < 0) r = -r, s = -s;
  return {r, s};
}
