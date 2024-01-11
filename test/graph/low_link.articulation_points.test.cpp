// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A

#include "graph/low_link.hpp"

int n, m; vector<int> G[100000];

int main() {
  scanf("%d%d", &n, &m);
  rep(i, m) {
    int u, v; scanf("%d%d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  auto vs = low_link(G).first;
  sort(all(vs));
  for (auto v : vs) if (v < n) printf("%d\n", v);
}
