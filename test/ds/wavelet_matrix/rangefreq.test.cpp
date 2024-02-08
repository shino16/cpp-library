// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2426

#include "ds/wavelet_matrix.hpp"
#include "util/comp.hpp"

int n, q, x[5000], y[5000], ix[5000], a[5000];

int main() {
  scanf("%d%d", &n, &q);
  rep(i, n) scanf("%d%d", &x[i], &y[i]);

  iota(ix, ix+n, 0);
  sort(ix, ix+n, [](int i, int j) { return x[i] < x[j]; });
  compress fy(y, y+n);
  rep(i, n) a[i] = fy(y[ix[i]]);
  sort(x, x+n);

  wavelet_matrix<int, 5001> wm(a, a+n);
  while (q--) {
    int l, u, r, d; scanf("%d%d%d%d", &l, &u, &r, &d);
    r++, d++;
    l = lower_bound(x, x+n, l) - x, r = lower_bound(x, x+n, r) - x;
    u = fy.lower_bound(u), d = fy.lower_bound(d);
    printf("%d\n", wm.rangefreq(l, r, u, d));
  }
}
