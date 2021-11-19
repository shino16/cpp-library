#pragma once
#include "prelude.hpp"
#include "type/alias.hpp"

template <class Iter, class F = plus<val_t<Iter>>>
vector<val_t<Iter>> cumsuml(Iter first, Iter last,
                            val_t<Iter> e = val_t<Iter>(), const F& f = F()) {
  vector<val_t<Iter>> res{e};
  res.reserve(last - first + 1);
  while (first != last) res.push_back(e = f(e, *first++));
  return res;
}

template <class Iter, class F = plus<val_t<Iter>>>
vector<val_t<Iter>> cumsumr(Iter first, Iter last,
                            val_t<Iter> e = val_t<Iter>(), const F& f = F()) {
  vector<val_t<Iter>> res{e};
  res.reserve(last - first + 1);
  while (first != last) res.push_back(e = f(e, *--last));
  reverse(res.begin(), res.end());
  return res;
}
