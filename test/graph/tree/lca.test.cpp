#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C"

#include "graph/tree/lca.hpp"

int n, q;
vector<int> G[100000];

int main() {
  scanf("%d", &n);
  rep(i, n) {
    int k; scanf("%d", &k);
    rep(_, k) {
      int c; scanf("%d", &c);
      G[i].push_back(c);
    }
  }
  lca lca(G);

  scanf("%d", &q);
  while (q--) {
    int u, v; scanf("%d%d", &u, &v);
    printf("%d\n", lca(u, v));
  }
}
