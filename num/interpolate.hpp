#pragma once
#include "mod/modint.hpp"
#include "types.hpp"
#include "ps/fps.hpp"

// find f(x) where deg f < size(a), f(s+i) = a[i]
template <
    class It,
    enable_if_t<is_base_of_v<atcoder::internal::modint_base, val_t<It>>>* = nullptr>
val_t<It> interpolate(It a, It last, val_t<It> x, val_t<It> s = 0) {
  x -= s;
  int n = last - a;
  val_t<It> fact = 1;
  rep(i, n - 1) fact *= i + 1;
  vector<val_t<It>> ifact(n), cuml(n + 1), cumr(n + 1);
  ifact[n - 1] = fact.inv();
  repr(i, n - 1) ifact[i] = ifact[i + 1] * (i + 1);
  cuml[0] = 1;
  rep(i, n) cuml[i + 1] = cuml[i] * (x - i);
  cumr[n] = 1;
  repr(i, n) cumr[i] = cumr[i + 1] * (x - i);
  val_t<It> ans = 0;
  rep(i, n) {
    ans += a[i] * cuml[i] * cumr[i + 1] * ifact[i] * ifact[n - i - 1] *
           ((n - i) % 2 ? 1 : -1);
  }
  return ans;
}
