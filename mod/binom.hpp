#pragma once
#include "mod/fact.hpp"

struct binom {
  int n, k;
  binom(int n, int k) : n(n), k(k) { }
  template <class T>
  operator T() const {
    return k < 0   ? T(0)
           : n < 0 ? binom(-n + k - 1, k) * T(k % 2 ? -1 : 1)
           : k > n ? T(0)
                   : (T)fact(n) * inv_fact(k) * inv_fact(n - k);
  }
};

struct binom_rep {
  int n, k;
  binom_rep(int n, int k) : n(n), k(k) { }
  template <class T>
  operator T() const {
    return binom(n + k - 1, k);
  }
};

template <class... Ts>
struct multinomial {
  array<int, sizeof...(Ts)> t;
  multinomial(Ts... xs) : t({xs...}) { }
  template <class T>
  operator T() const {
    T ans(1);
    int n = accumulate(all(t), 0);
    rep(i, t.size() - 1) ans *= binom(n, t[i]), n -= t[i];
    return ans;
  }
};
