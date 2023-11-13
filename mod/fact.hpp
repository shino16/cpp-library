#pragma once
#include "mod/inv.hpp"

struct fact {
  int n;
  fact(int n) : n(n) { }
  template <class T>
  operator T() const {
    static vector<T> fact = {T(1)};
    if (fact.size() <= n) {
      int l = fact.size();
      fact.resize(n * 2);
      rep2(i, l, n * 2) fact[i] = fact[i - 1] * i;
    }
    return fact[n];
  }
};

struct inv_fact {
  int n;
  inv_fact(int n) : n(n) { }
  template <class T>
  operator T() const {
    static vector<T> inv_fact = {T(1)};
    if (inv_fact.size() <= n) {
      int l = inv_fact.size();
      inv_fact.resize(n * 2);
      rep2(i, l, n * 2) inv_fact[i] = inv_fact[i - 1] * inverse(i);
    }
    return inv_fact[n];
  }
};
