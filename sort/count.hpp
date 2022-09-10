#pragma once
#include "types.hpp"
#include "func/id.hpp"

// Stable sort
template <class It, class Key = identity>
void count_sort(It first, It last, int max_key, Key key = Key()) {
  vector<int> cnt(max_key + 1);
  for (auto it = first; it != last; it++) cnt[key(*it)]++;
  exclusive_scan(all(cnt), cnt.begin(), 0);
  vector<val_t<It>> res(distance(first, last));
  for (auto it = first; it != last; it++) res[cnt[key(*it)]++] = move(*it);
  move(all(res), first);
}
