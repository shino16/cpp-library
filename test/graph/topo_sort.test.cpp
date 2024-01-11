// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_A

#include "graph/topo_sort.hpp"

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<vector<int>> G(n);
  rep(_, m) {
    int u, v;
    scanf("%d%d", &u, &v);
    G[u].push_back(v);
  }
  printf("%d\n", int(!topo_sort(G).has_value()));
}
