#pragma once
#include "mod/fact.hpp"

template <class T = atcoder::modint998244353>
T binom(int n, int k) {
  return k < 0 ? T(0)
       : n < 0 ? binom<T>(-n + k - 1, k) * T(k % 2 ? -1 : 1)
       : k > n ? T(0)
               : fact<T>(n) * inv_fact<T>(k) * inv_fact<T>(n - k);
}

template <class T = atcoder::modint998244353>
T binom_rep(int n, int k) { return binom<T>(n + k - 1, k); }

template <class T = atcoder::modint998244353>
T multinomial(initializer_list<int> ks) {
  T ans(1);
  int n = accumulate(all(ks), 0);
  rep(i, ks.size() - 1) ans *= binom<T>(n, ks.begin()[i]), n -= ks.begin()[i];
  return ans;
}
