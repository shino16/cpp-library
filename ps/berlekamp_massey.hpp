#pragma once
#include "prelude.hpp"
#include "types.hpp"
#include "atcoder/modint"

template <class It>
vector<val_t<It>> berlekamp_massey(It a, It a_last) {
  using T = val_t<It>;
  int intro = 0;
  while (a != a_last && *a == T(0)) a++, intro++;
  if (a == a_last) return {};
  vector<T> q, q2, p = {T(0)};
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
  p.insert(p.begin(), intro, T(0));
  return p;
}
