// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A

#include "graph/kruskal.hpp"

int main() {
  int n, m; scanf("%d%d", &n, &m);
  vector<tuple<int, int, int>> edges(m);
  rep(i, m) {
    int s, t, w; scanf("%d%d%d", &s, &t, &w);
    edges[i] = {s, t, w};
  }
  ll tot = 0;
  for (auto [u, v, w] : kruskal(n, edges)) tot += w;
  printf("%lld\n", tot);
}
