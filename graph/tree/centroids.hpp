#pragma once
#include "graph.hpp"
#include "prelude.hpp"

struct cd_result {
 public:
  int root, max_depth;
  vector<int> par, ord, depth;
  vector<vector<int>> ch;
  // desc[c] = tree with centroid c, sorted by dist
  vector<vector<int>> desc;
  // dist[d][v] = distance to centroid with depth d
  vector<vector<int>> dist;

  int dist_from_centroid(int c, int v) const { return dist[depth[c]][v]; }

  using weight_type = void;
  template <class F>
  void adj(int v, F f) const {
    if (par[v] != -1) f(unit_edge{par[v]});
    for (auto u : ch[v]) f(unit_edge{u});
  }
  int deg(int v) const { return ch[v].size() + (par[v] != -1); }
  int size() const { return par.size(); }
};

// Assumes connectedness
template <class G, class = decltype(declval<G>()[int{}])>
cd_result centroid_decomposition(const G& graph) {
  graph_trait g(graph);
  int n = g.size();

  vector<int> par(n), ord, depth(n, -1), sz(n);
  vector<vector<int>> ch(n), desc(n), dist;
  vector<int> cnt(n);

  auto main = [&](auto&& f_main, int r, int d) -> int {
    auto sz_dfs = [&](auto&& f, int v, int p) -> int {
      int sz_v = 1;
      for (int u : g[v])
        if (depth[u] == -1 && u != p) sz_v += f(f, u, v);
      return sz[v] = sz_v;
    };
    sz_dfs(sz_dfs, r, -1);
    int total = sz[r];

    auto find_c = [&](auto&& f, int v, int p) -> int {
      for (int u : g[v])
        if (depth[u] == -1 && u != p && sz[u] * 2 > total) return f(f, u, v);
      return v;
    };
    int c = find_c(find_c, r, -1);

    ord.push_back(c);
    depth[c] = d;
    if (dist.size() <= d) dist.resize(d + 1);
    dist[d].resize(n, INT_MAX);
    auto& desc_c = desc[c];
    auto& dists_d = dist[d];
    desc_c.reserve(total);
    int max_d = 0;

    auto dist_dfs = [&](auto&& f, int v, int p, int dis) -> void {
      desc_c.push_back(v);
      dists_d[v] = dis;
      max_d = max(max_d, dis);
      for (int u : g[v])
        if (depth[u] == -1 && u != p) f(f, u, v, dis + 1);
    };
    dist_dfs(dist_dfs, c, -1, 0);

    fill(cnt.begin(), cnt.begin() + max_d + 1, 0);
    for (auto v : desc_c) cnt[dists_d[v]]++;
    partial_sum(cnt.begin(), cnt.begin() + max_d + 1, cnt.begin());
    vector<int> desc2(total);
    for (auto v : desc_c) desc2[--cnt[dists_d[v]]] = v;
    desc_c = move(desc2);

    for (auto u : g[c])
      if (depth[u] == -1) {
        int c2 = f_main(f_main, u, d + 1);
        par[c2] = c;
        ch[c].push_back(c2);
      }

    return c;
  };
  int c = main(main, 0, 0);
  par[c] = -1;
  int max_depth = *max_element(all(depth));

  return {c, max_depth, par, ord, depth, ch, desc, dist};
}
