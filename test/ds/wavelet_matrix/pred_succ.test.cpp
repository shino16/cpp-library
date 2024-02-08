// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1549

#include "ds/wavelet_matrix.hpp"

int n, a[100000];
int q;

int main() {
  scanf("%d", &n);
  rep(i, n) scanf("%d", a + i);
  scanf("%d", &q);
  const int ofs = 1000000;
  rep(i, n) a[i] += ofs;
  wavelet_matrix<int, 2000002> wm(a, a + n);
  while (q--) {
    int l, r, d;
    scanf("%d%d%d", &l, &r, &d);
    r++;
    d += ofs;
    int dif = INT_MAX, x;
    for (int v : (unsigned[]){wm.pred(l, r, d), wm.succ(l, r, d)})
      if (v != -1)
        if (dif > abs(d - v)) dif = abs(d - v), x = v;
    printf("%d\n", abs(d - x));
  }
}
