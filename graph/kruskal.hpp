#pragma once
#include "graph.hpp"
#include "ds/dsu.hpp"

// G: undirected
// forest if not connected
template <class G>
vector<tuple<int, int, weight_t<G>>> kruskal(const G& graph) {
  graph_trait<G> g(graph);
  vector<tuple<weight_t<G>, int, int>> edges;
  rep(v, g.size()) g.adj(v, [&](auto&& e) {
    if (e.to > v) edges.emplace_back(e.w(), v, e.to);
  });
  kruskal(g.size(), move(edges));
}

template <class weight_t>
vector<tuple<int, int, weight_t>> kruskal(int n, vector<tuple<int, int, weight_t>> edges) {
  sort(all(edges), [&](auto&& a, auto&& b) { return get<2>(a) < get<2>(b); });
  dsu dsu(n);
  vector<tuple<int, int, weight_t>> res;
  for (auto [u, v, w] : edges)
    if (dsu.unite(u, v)) res.emplace_back(u, v, w);
  return res;
}
