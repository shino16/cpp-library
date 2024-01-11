// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2415

#include "dp/knuth_merge.hpp"

int k, n;
ll w[4000], sum[4001];

int main() {
  scanf("%d", &n);
  rep(i, n) scanf("%lld", w+i);
  rep(i, n) sum[i+1] = sum[i] + w[i];
  auto ans = knuth_merge_dp(n, [](int l, int r) { return sum[r] - sum[l]; });
  printf("%lld\n", ans[0][n]);
}
