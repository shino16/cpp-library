#pragma once
#include "prelude.hpp"
#include "arith/sqrt.hpp"

// { m//d for d in [1..m] }
template <class T>
vector<T> quotients(T m) {
  int l = floor_sqrt(m), k = m / (l + 1);
  vector<T> qs(l + k);
  rep(i, l) qs[i] = i + 1;
  rep(i, k) qs[i + l] = m / (k - i);
  return qs;
}
