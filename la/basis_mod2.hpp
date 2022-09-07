#pragma once
#include "types.hpp"

template <class It>
vector<val_t<It>> basis_mod2(It a, It a_last) {
  vector<val_t<It>> res;
  while (a != a_last) {
    auto x = *a++;
    for (auto e : res) x = min(x, x ^ e);
    if (x) res.push_back(x);
  }
  return res;
}
