#define PROBLEM "https://www.hackerrank.com/contests/world-codesprint-5/challenges/mining/problem"

#include "dp/knuth_partition.hpp"

int k, n, w[1000000], x[1000000];
ll cost[5001][5001];

int main() {
  scanf("%d%d", &n, &k);
  rep(i, n) scanf("%d%d", &x[i], &w[i]);
  rep(l, n) {
    int k = l;
    ll wl = w[l], wr = 0;
    ll c = cost[l][l + 1] = 0;
    rep2(r, l + 1, n) {
      wr += w[r], c += 1LL * (x[r] - x[k]) * w[r];
      while (k < r && wl < wr) {
        c = c + (wl - wr) * (x[k + 1] - x[k]);
        k++;
        wl += w[k], wr -= w[k];
      }
      cost[l][r + 1] = c;
    }
  }
  auto dp = knuth_partition_dp(k, n, [](int l, int r) { return cost[l][r]; });
  printf("%lld", dp[n]);
}
