#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_D"

#include "ds/dual_segtree.hpp"

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  auto op = [](unsigned a, unsigned b) { return ~b ? b : a; };
  dual_segment_tree st(n, unsigned(1 << 31) - 1, monoid(CONST(~0u), op), op);
  while (q--) {
    int cmd;
    scanf("%d", &cmd);
    if (cmd == 0) {
      int s, t, x;
      scanf("%d%d%d", &s, &t, &x);
      st.apply(s, t + 1, x);
    } else {
      int i;
      scanf("%d", &i);
      printf("%u\n", st.get(i));
    }
  }
}
