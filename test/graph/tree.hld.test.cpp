// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2667

#include "graph/tree/hld.hpp"
#include "ds/range_fenwick.hpp"

int n, q;
vector<int> G[150000];
int c, u, v;

int main() {
  scanf("%d%d", &n, &q);
  rep(_, n - 1) {
    int u, v;
    scanf("%d%d", &u, &v);
    G[u].push_back(v);
  }
  hld hld(G, 0);
  range_fenwick_tree fwk(n, addition<ll>{}, multiplies<ll>{});
  while (q--) {
    scanf("%d%d%d", &c, &u, &v);
    if (c == 0) {
      ll ans = 0;
      hld.paths(u, v, [&](int l, int r) { ans += fwk.sum(l, r); });
      printf("%lld\n", ans);
    } else {
      hld.subtree(u, [&](int l, int r) { fwk.add(l, r, v); });
    }
  }
}
