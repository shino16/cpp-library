#pragma once
#include "prelude.hpp"
#include "types.hpp"

template <class Iter>
auto rle(Iter first, Iter last) -> vector<pair<val_t<Iter>, int>> {
  vector<pair<val_t<Iter>, int>> v;
  v.reserve(last - first);
  if (first != last) v.emplace_back(*first++, 1);
  for (; first != last; first++) {
    if (*first == v.back().first) v.back().second++;
    else v.emplace_back(*first, 1);
  }
  return v;
}
