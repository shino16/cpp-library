#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "ds/sparse_table.hpp"

int n, q, a[500000], l, r;

int main() {
  scanf("%d%d", &n, &q);
  rep(i, n) scanf("%d", a+i);
  sparse_table<minimum<int>> rmq(a, a+n);
  while (q--) {
    scanf("%d%d", &l, &r);
    printf("%d\n", rmq.prod(l, r));
  }
}
