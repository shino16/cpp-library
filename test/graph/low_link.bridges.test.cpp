#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B"

#include "graph/low_link.hpp"

int n, m; vector<int> G[100000];

int main() {
  scanf("%d%d", &n, &m);
  rep(i, m) {
    int u, v; scanf("%d%d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  auto es = low_link(G).second;
  for (auto& [u, v] : es) tie(u, v) = minmax({u, v});
  sort(all(es));
  for (auto [u, v] : es) printf("%d %d\n", u, v);
}
