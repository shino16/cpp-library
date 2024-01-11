// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/static_range_sum

#include "ds/disjoint_sparse_table.hpp"

int n, q, a[500000];

int main() {
  scanf("%d%d", &n, &q);
  rep(i, n) scanf("%d", a+i);
  disjoint_sparse_table<addition<ll>> dst(a, a+n);
  while (q--) {
    int l, r; scanf("%d%d", &l, &r);
    printf("%lld\n", dst.prod(l, r));
  }
}
