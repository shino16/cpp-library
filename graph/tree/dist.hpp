#pragma once
#include "graph/tree/dfs.hpp"

template <class G>
vector<W<G>> distances(const G& graph, int s) {
  graph_trait<G> g(graph);
  vector<W<G>> res(g.size(), numeric_limits<W<G>>::max());
  res[s] = W<G>(0);
  dfs(graph, s, [&](auto&& e, int p) { res[e.to] = res[p] + e.w(); });
  return res;
}
