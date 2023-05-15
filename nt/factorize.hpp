#pragma once
#include "prelude.hpp"
#include "bit/ctz.hpp"

template <class T>
vector<pair<T, int>> factorize(T n) {
  assert(n >= 1);
  vector<pair<T, int>> ans;
  int t = ctz(n);
  if (t) ans.emplace_back(2, t), n >>= t;
  for (T d = 3; d * d <= n; d += 2) if (n % d == 0) {
    int k = 0;
    while (n % d == 0) n /= d, k++;
    ans.emplace_back(d, k);
  }
  if (n != 1) ans.emplace_back(n, 1);
  return ans;
}
