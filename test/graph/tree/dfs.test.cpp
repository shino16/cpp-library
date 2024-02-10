// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/tree_diameter

#include "io.hpp"
#include "graph/tree/dfs.hpp"
#include "graph/csr.hpp"

int main() {
  int n = in;
  auto es = in.vec<tuple<int, int, ll>>(n-1);
  auto G = csr_graph<ll>(in, all(es));
  vector<ll> d(n);
  dfs(G, 0, [&](auto e, int p) { d[e.to] = d[p] + e.w(); });
  int s = max_element(all(d)) - d.begin();
  d[s] = 0;
  vector<int> par(n);
  dfs(G, s, [&](auto e, int p) { d[e.to] = d[par[e.to] = p] + e.w(); });
  int t = max_element(all(d)) - d.begin();
  vector<int> vs = {t}; vs.reserve(n);
  while (vs.back() != s) vs.push_back(par[vs.back()]);
  out(d[t], vs.size());
  out.iter(all(vs));
}
