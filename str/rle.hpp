#pragma once
#include "prelude.hpp"

template <class Iter>
auto rle(Iter first, Iter last) -> vector<pair<decltype(*first), int>> {
  vector<pair<decltype(*first), int>> v;
  v.reserve(last - first);
  if (first != last) v.emplace_back(*first++, 1);
  for (; first != last; first++) {
    if (*first == v.back().first) v.back().second++;
    else v.emplace_back(*first, 1);
  }
  return v;
}
