#pragma once
#include "graph.hpp"

template <class G>
optional<vector<int>> topo_sort(const G& graph) {
  graph_trait<G> g(graph);
  vector<int> deg(g.size()), nxt, res;
  nxt.reserve(g.size());
  res.reserve(g.size());
  rep(v, g.size()) g.adj(v, [&](int u) { deg[u]++; });
  rep(v, g.size()) if (deg[v] == 0) nxt.push_back(v);
  int i = 0;
  while (i != nxt.size()) {
    int v = nxt[i++];
    res.push_back(v);
    g.adj(v, [&](int u) {
      if (--deg[u] == 0) nxt.push_back(u);
    });
  }
  return nxt.size() == g.size() ? optional<vector<int>>(nxt) : nullopt;
}
