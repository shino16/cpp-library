#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A"

#include "prelude.hpp"
#include "graph/dijkstra.hpp"

int n, m, r;
vector<pair<int, int>> G[100000];

int main() {
  scanf("%d%d%d", &n, &m, &r);
  rep(_, m) {
    int u, v; int w; scanf("%d%d%d", &u, &v, &w);
    G[u].emplace_back(v, w);
  }
  auto d = dijkstra(G, r);
  rep(i, n) if (d[i] == INT_MAX) printf("INF\n"); else printf("%d\n", d[i]);
}
