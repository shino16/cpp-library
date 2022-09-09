#pragma once
#include "types.hpp"

template <class It>
vector<val_t<It>> basis_mod2(It first, It last) {
  vector<val_t<It>> res;
  while (first != last) {
    auto x = *first++;
    for (auto e : res) x = min(x, x ^ e);
    if (x) res.push_back(x);
  }
  return res;
}
