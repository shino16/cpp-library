#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"

#include "prelude.hpp"
#include "ds/segtree.hpp"

int main() {
  int n, q, c, x, y;
  scanf("%d%d", &n, &q);
  segment_tree rsq(n, monoid([] { return 0; }, plus{}));
  while (q--) {
    scanf("%d%d%d", &c, &x, &y);
    if (c == 0)
      rsq.add(x - 1, y);
    else
      printf("%d\n", rsq.prod(x - 1, y));
  }
}
