#define PROBLEM "https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14"

#include "dp/d_and_c.hpp"

int n, k, a[8000];
ll sum[8001];

int main() {
  scanf("%d%d", &n, &k);
  rep(i, n) scanf("%d", a+i);
  rep(i, n) sum[i+1] = sum[i] + a[i];
  auto cost = [](int l, int r) {
    return (sum[r] - sum[l]) * (r - l);
  };
  auto dp = d_and_c_dp(k, n, cost);
  printf("%lld", dp[n]);
}
