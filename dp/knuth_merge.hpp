#pragma once
#include "prelude.hpp"

// O(n^2)
// Starts with dp(l, r) = 0 (r - l <= 1) and
// dp(l, r) = min { dp(l, k) + dp(k, r) + cost(l, r) : l < k < r }
// Returns dp(0, n)
template <class F>
auto knuth_merge_dp(int n, F cost) {
  using T = decltype(cost(0, 0));
  vector<vector<T>> dp(n + 1, vector<T>(n + 1, numeric_limits<T>::max() / 2));
  vector<int> opt(n + 2), opt2(n + 2);
  repr(k, n + 1) {
    dp[k][k] = T(0), opt[k] = k;
    if (k + 1 <= n) dp[k][k + 1] = T(0);
    rep2(i, k + 2, n + 1) rep2(j, max(k + 1, opt2[i - 1]), min(i, opt[i] + 1)) {
      if (dp[k][i] > dp[k][j] + dp[j][i] + cost(k, i))
        dp[k][i] = dp[k][j] + dp[j][i] + cost(k, i), opt2[i] = j;
    }
    swap(opt, opt2);
  }
  return dp[0][n];
}
