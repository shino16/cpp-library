#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "ds/wavelet_matrix.hpp"

int n, q, a[200000];

int main() {
  scanf("%d%d", &n, &q);
  rep(i, n) scanf("%d", a+i);

  wavelet_matrix<1000000001> wm(a, a+n);
  while (q--) {
    int l, r, k; scanf("%d%d%d", &l, &r, &k);
    printf("%d\n", wm.rquantile(l, r, k));
  }
}
