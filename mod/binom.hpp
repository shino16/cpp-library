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
