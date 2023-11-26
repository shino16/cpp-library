#pragma once
#include "prelude.hpp"

// Returns (min f, min argmin f)
template <class T, class F>
auto convex_min(T l, T r, F f) {
  if (l + 1 == r) return pair(f(l), l);

  auto sf = [l, r, &f](T x) {
    return x < r ? f(x) : numeric_limits<T>::max();
  };

  const double PHI = 1.6180339887498948;
  vector<T> fib = {T(1), T(1)};
  fib.reserve(log((r - l + 1) / PHI) + 1);
  while (fib.back() <= r - l) fib.push_back(fib.end()[-1] + fib.end()[-2]);
  int i = fib.size();
  l = l - 1, r = l + fib[--i];
  T x = l + fib[i-2], y = l + fib[i-1];
  auto fx = sf(x), fy = sf(y);
  while (i >= 4) {
    if (fx > fy) {
      l = x;
      tie(x, fx) = pair(y, fy);
      y = l + fib[--i - 1];
      fy = sf(y);
    } else {
      r = y;
      tie(y, fy) = pair(x, fx);
      x = l + fib[--i - 2];
      fx = sf(x);
    }
  }
  return fx > fy ? pair(fy, y) : pair(fx, x);
}
