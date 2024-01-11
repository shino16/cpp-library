// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B

#include "prelude.hpp"
#include "graph/bellman_ford.hpp"

int n, m, r;
vector<pair<int, int>> G[1000];

int main() {
  scanf("%d%d%d", &n, &m, &r);
  rep(_, m) {
    int u, v; int w; scanf("%d%d%d", &u, &v, &w);
    G[u].emplace_back(v, w);
  }
  auto [b, dist] = bellman_ford(G, r);
  if (b) printf("NEGATIVE CYCLE\n");
  else rep(i, n) if (dist[i] == INT_MAX) printf("INF\n"); else printf("%d\n", dist[i]);
}
