#pragma once
#include "prelude.hpp"

// O(n log n) (O(n) if we can skip binary search)
// Minimizes cost of partitions of [0, n)
// Requires cost(a,c) + cost(b,d) <= cost(a,d) + cost(b,c)
// for a < b < c < d (wider is worse).
template <class F>
auto dp_1d1d(int n, F cost) {
  using T = decltype(cost(0, 0));
  vector<T> dp(n+1);
  // opt[_] = argmin_{j<=k} (dp[j] + cost(j, i)) on k < ix[_] <= i < ix[_+1]
  vi opt(n+1), ix(n+1);
  int l = 0, r = ix[0]++; // opt[l:r+1] is a deque
  rep2(k, 1, n+1) {
    dp[k] = dp[opt[l]] + cost(opt[l], k);
    assert(l+1 < n);
    if (++ix[l] == ix[l+1] && l < r) l++;
    while (l <= r && dp[opt[r]] + cost(opt[r], ix[r]) > dp[k] + cost(k, ix[r])) r--;
    if (opt[++r] = k, l == r) continue;
    int lo = ix[--r], hi = n+1; // Finds hi = where opt's value becomes k
    while (hi - lo > 1) {
      int m = (lo + hi) / 2;
      (dp[opt[r]] + cost(opt[r], m) > dp[k] + cost(k, m) ? hi : lo) = m;
    }
    if (hi <= n) opt[++r] = k, ix[r] = hi;
  }
  return dp;
}
