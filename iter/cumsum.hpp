#pragma once
#include "prelude.hpp"
#include "types.hpp"

template <class It, class T = val_t<It>, class F = plus<T>>
vector<T> cumsuml(It first, It last, T e = T(), const F& f = F()) {
  vector<T> res{e};
  res.reserve(last - first + 1);
  while (first != last) res.push_back(e = f(e, *first++));
  return res;
}

template <class It, class T = val_t<It>, class F = plus<T>>
vector<T> cumsumr(It first, It last, T e = T(), const F& f = F()) {
  vector<T> res{e};
  res.reserve(last - first + 1);
  while (first != last) res.push_back(e = f(e, *--last));
  reverse(res.begin(), res.end());
  return res;
}
