// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_B

#include "graph/tree/rerooting.hpp"

int main() {
  int n;
  scanf("%d", &n);
  vector<vector<pair<int, int>>> G(n);
  rep(_, n - 1) {
    int u, v;
    int w;
    scanf("%d%d%d", &u, &v, &w);
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }
  auto res = rerooting(
      G, pair(pair(0, -1), pair(0, -1)),
      [&](auto& xu, auto& xv, int v, int w) {
        if (xu.first.first < xv.first.first + w)
          xu.second = xu.first, xu.first = pair(xv.first.first + w, v);
        else if (xu.second.first < xv.first.first + w)
          xu.second = pair(xv.first.first + w, v);
      },
      [&](auto& xu, auto&&, int v, auto&&) {
        if (xu.first.second == v) xu.first = xu.second;
      });
  rep(v, n) printf("%d\n", res[v].first.first);
}
