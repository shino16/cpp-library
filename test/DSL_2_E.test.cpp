#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E"

#include "prelude.hpp"
#include "ds/fenwick.hpp"

int n, q, c, s, t, x, i;

int main() {
  scanf("%d%d", &n, &q);
  fenwick_tree<addition<int>> fwk(n+1);
  while (q--) {
    scanf("%d", &c);
    if (c == 0) {
      scanf("%d%d%d", &s, &t, &x);
      fwk.add(s-1, x);
      fwk.sub(t, x);
    } else {
      scanf("%d", &i);
      printf("%d\n", fwk.sum(i));
    }
  }
}
