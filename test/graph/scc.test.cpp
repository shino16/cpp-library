// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C

#include "graph/bellman_ford.hpp"
#include "graph/ford_fulkerson.hpp"
#include "graph/scc.hpp"
#include "prelude.hpp"

int n, m;
vector<pair<int, ll>> G[100];

int main() {
  scanf("%d%d", &n, &m);
  rep(_, m) {
    int u, v;
    int w;
    scanf("%d%d%d", &u, &v, &w);
    G[u].emplace_back(v, w);
  }
  scc scc(G);
  for (auto& vs : scc.groups())
    if (bellman_ford(G, vs[0]).first) return printf("NEGATIVE CYCLE\n"), 0;
  auto d = ford_fulkerson(G);
  rep(v, n) rep(i, n) printf(
      "%s%c", d[v][i] == LONG_LONG_MAX ? "INF" : to_string(d[v][i]).c_str(),
      " \n"[i == n - 1]);
}