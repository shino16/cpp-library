#pragma once
#include "types.hpp"
#include "func/id.hpp"

// Stable sort
template <class It, class Key = ident>
void count_sort(It a, It a_last, int max_key, Key key = Key()) {
  vector<int> cnt(max_key + 1);
  for (auto it = a; it != a_last; it++)
    cnt[key(*it)]++;
  exclusive_scan(all(cnt), cnt.begin(), 0);
  vector<val_t<It>> res(distance(a, a_last));
  for (auto it = a; it != a_last; it++)
    res[cnt[key(*it)]++] = move(*it);
  move(all(res), a);
}
