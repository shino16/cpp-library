#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2842"

#include "prelude.hpp"
#include "ds/fenwick2d.hpp"

int h, w, T, q;
tuple<int, int, int> trans[100000], *l = trans, *r = trans;

int main() {
  scanf("%d%d%d%d", &h, &w, &T, &q);
  fenwick_tree_2d<addition<int>> a(h, w), b(h, w);
  while (q--) {
    int t, c, i, j; scanf("%d%d%d%d", &t, &c, &i, &j);
    i--, j--;
    while (l != r && get<0>(*l) <= t) {
      auto [x, s, T] = *l++;
      a.sub(s, T, 1);
      b.add(s, T, 1);
    }
    if (c == 0) {
      a.add(i, j, 1);
      *r++ = {t+T, i, j};
    } else if (c == 1) {
      b.assign(i, j, 0);
    } else {
      int i2, j2; scanf("%d%d", &i2, &j2);
      printf("%d %d\n", b.sum(i, j, i2, j2), a.sum(i, j, i2, j2));
    }
  }
}
