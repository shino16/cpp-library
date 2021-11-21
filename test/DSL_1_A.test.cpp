#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A"

#include "prelude.hpp"
#include "ds/uf.hpp"

int n, q, c, x, y;
int main() {
   scanf("%d%d", &n, &q);
   union_find uf(n);
   while (q--) {
      scanf("%d%d%d", &c, &x, &y);
      if (c == 0) uf.unite(x, y);
      else printf("%d\n", (int)uf.same(x, y));
   }
}