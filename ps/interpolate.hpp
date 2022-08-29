#pragma once
#include "atcoder/modint"
#include "prelude.hpp"

// find f(x) where deg f < size(a), f(s+i) = a[i]
template <
    class It, class T,
    enable_if_t<is_base_of_v<atcoder::internal::modint_base, T>>* = nullptr>
T interpolate(It a, It a_last, T x, T s = 0) {
  x -= s;
  int n = a_last - a;
  T fact = 1;
  rep(i, n - 1) fact *= i + 1;
  vector<T> ifact(n), cuml(n + 1), cumr(n + 1);
  ifact[n - 1] = fact.inv();
  repr(i, n - 1) ifact[i] = ifact[i + 1] * (i + 1);
  cuml[0] = 1;
  rep(i, n) cuml[i + 1] = cuml[i] * (x - i);
  cumr[n] = 1;
  repr(i, n) cumr[i] = cumr[i + 1] * (x - i);
  T ans = 0;
  rep(i, n) {
    ans += a[i] * cuml[i] * cumr[i + 1] * ifact[i] * ifact[n - i - 1] *
           ((n - i) % 2 ? 1 : -1);
  }
  return ans;
}
