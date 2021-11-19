#pragma once
#include "prelude.hpp"

template <class T>
class Binom {
 public:
  Binom(int n) : fact_(n), ifact_(n) {
    fact_[0] = T(1);
    for (int i = 0; i < n - 1; i++) assert(fact_[i] != 0), fact_[i + 1] = fact_[i] * T(i + 1);
    ifact_[n - 1] = T(1) / fact_[n - 1];
    for (int i = n - 1; i--;) ifact_[i] = ifact_[i + 1] * T(i + 1);
  }
  T operator()(int n, int k) const {
    return k < 0 || k > n ? T(0) : fact_[n] * ifact_[k] * ifact_[n - k];
  }
  T with_rep(int n, int k) const { return (*this)(n + k - 1, k); }
  T fact(int n) const { return fact_[n]; }
  T ifact(int n) const { return ifact_[n]; }

 private:
  vector<T> fact_, ifact_;
};
