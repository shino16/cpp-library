#pragma once
#include "mod/fact.hpp"

template <class T = atcoder::modint998244353>
T binom(int n, int k) {
  return k < 0 ? T(0)
       : n < 0 ? binom(-n + k - 1, k) * T(k % 2 ? -1 : 1)
       : k > n ? T(0)
               : (T)fact(n) * inv_fact(k) * inv_fact(n - k);
}

template <class T = atcoder::modint998244353>
T binom_rep(int n, int k) { return binom(n + k - 1, k); }

template <class T = atcoder::modint998244353>
T multinomial(initializer_list<int> ks) {
  T ans(1);
  int n = accumulate(all(ks), 0);
  rep(i, ks.size() - 1) ans *= binom(n, ks.begin()[i]), n -= ks.begin()[i];
  return ans;
}
