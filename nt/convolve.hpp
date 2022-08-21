#pragma once
#include "types.hpp"
#include "nt/primes.hpp"

// deg defaults to a_last - a
template <class It1, class It2>
auto convolve(It1 a, It1 a_last, It2 b, It2 b_last, int deg = -1) {
  int n = a_last - a, m = b_last - b;
  if (deg == -1) deg = n;
  vector<decltype(a[0] * b[0])> res(deg);
  rep2(i, 1, min(n, deg)) rep2(j, 1, m) {
    if (i * j >= deg) break;
    res[i * j] += a[i] * b[j];
  }
  return res;
}

// deg defaults to a_last - a
// a[1] = 1, a[nm] = a[n] * a[m] if gcd(n, m) == 1
template <class It1, class It2>
auto convolve_multiplicative(It1 a, It1 a_last, It2 b, It2 b_last,
                             int deg = -1) {
  int n = a_last - a, m = b_last - b;
  if (deg == -1) deg = n;
  vector<decltype(a[0] * b[0])> res(deg);
  copy(b, b + min(m, deg), res.begin());
  for (auto p : primes(deg)) {
    repr2(i, 1, (deg - 1) / p + 1) {
      int n = p * i;
      for (int q = p, m = i; ; q *= p, m /= p) {
        res[n] += a[q] * res[m];
        if (m % p != 0) break;
      }
    }
  }
  return res;
}
