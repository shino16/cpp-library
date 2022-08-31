#pragma once
#include "graph/tree/dfs.hpp"

template <class G>
vector<weight_t<G>> distances(const G& graph, int s) {
  graph_trait<G> g(graph);
  vector<weight_t<G>> res(g.size(), numeric_limits<weight_t<G>>::max());
  res[s] = weight_t<G>(0);
  dfs(graph, s, [&](auto&& e, int p) { res[e.to] = res[p] + e.w(); });
  return res;
}
