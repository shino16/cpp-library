#pragma once
#include "prelude.hpp"
#include "types.hpp"
#include "ps/frac.hpp"

template <class It>
vector<val_t<It>> berlekamp_massey(It a, It a_last) {
  using T = val_t<It>;
  int init = 0;
  while (a != a_last && *a == T(0)) a++, init++;
  if (a == a_last) return {};
  vector<T> q, q2, p(init + 1, T(0));
  for (auto v : {&q, &q2, &p}) v->reserve(a_last - a);
  T d = *a++;
  int t = 1;
  for (; a != a_last; a++, t++) {
    T eval(0);
    rep(i, p.size()) eval += p[i] * a[-i - 1];
    if (eval != *a) {
      T e = *a - eval, r = e / d;
      bool to_swap = t + q.size() > p.size();
      if (to_swap) q2 = p;
      p.resize(max(p.size(), q.size() + t));
      p[t - 1] += r;
      rep(i, q.size()) p[t + i] -= r * q[i];
      if (to_swap) swap(q2, q), d = e, t = 0;
    }
  }
  return p;
}

template <class It>
fraction<val_t<It>> find_generating_function(It a, It a_last) {
  using T = val_t<It>;
  using fps = formal_power_series<T>;
  fps denom = berlekamp_massey(a, a_last);
  for (auto& e : denom) e = -e;
  denom.insert(denom.begin(), 1);
  fps numer(a, a + denom.size() - 1);
  numer = move(numer).conv(denom, denom.size() - 1);
  while (denom.back() == 0) denom.pop_back();
  return fraction<T>(move(numer), move(denom));
}
