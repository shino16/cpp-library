#pragma once
#include "graph.hpp"
#include "ds/dsu.hpp"

template <class weight_t>
vector<tuple<int, int, weight_t>> kruskal(int n, vector<tuple<int, int, weight_t>> edges) {
  sort(all(edges), [&](auto&& a, auto&& b) { return get<2>(a) < get<2>(b); });
  dsu dsu(n);
  vector<tuple<int, int, weight_t>> res;
  for (auto [u, v, w] : edges)
    if (dsu.unite(u, v)) res.emplace_back(u, v, w);
  return res;
}

// G: undirected
// forest if not connected
template <class G>
vector<tuple<int, int, weight_t<G>>> kruskal(const G& graph) {
  graph_trait<G> g(graph);
  vector<tuple<int, int, weight_t<G>>> edges;
  rep(v, g.size()) g.adj(v, [&](auto&& e) {
    if (e.to > v) edges.emplace_back(v, e.to, e.w());
  });
  return kruskal(g.size(), move(edges));
}

