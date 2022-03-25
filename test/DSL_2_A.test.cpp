#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_A"

#include "prelude.hpp"
#include "ds/segtree.hpp"

int main() {
  int n, q, c, x, y;
  scanf("%d%d", &n, &q);
  segment_tree rmq(n, monoid(CONST(INT_MAX), WRAP_FN(min)));
  while (q--) {
    scanf("%d%d%d", &c, &x, &y);
    if (c == 0)
      rmq.set(x, y);
    else
      printf("%d\n", rmq.prod(x, y + 1));
  }
}
