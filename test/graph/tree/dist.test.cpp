// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A

#include "graph/tree/dist.hpp"

int main() {
  int n; scanf("%d", &n);
  vector<vector<pair<int, int>>> G(n);
  rep(_, n-1) {
    int u, v; int w; scanf("%d%d%d", &u, &v, &w);
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }
  auto d = distances(G, 0);
  d = distances(G, max_element(all(d)) - d.begin());
  printf("%d\n", *max_element(all(d)));
}
