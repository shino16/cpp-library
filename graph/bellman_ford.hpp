#pragma once
#include "graph.hpp"

// (fail, dist)
template <class G>
pair<bool, vector<weight_t<G>>> bellman_ford(G& graph, int s) {
  const weight_t<G> inf = numeric_limits<weight_t<G>>::max();
  graph_trait<G> g(graph);
  vector<weight_t<G>> dist(g.size(), inf);
  dist[s] = 0;
  bool success = false;
  rep(t, g.size()) {
    bool updated = false;
    rep(v, g.size()) if (dist[v] != inf) g.adj(v, [&](auto&& e) {
      if (dist[e.to] > dist[v] + e.w())
        updated = true,
        dist[e.to] = dist[v] + e.w();
    });
    if (!updated) {
      success = true;
      break;
    }
  }
  for (auto& d : dist) if (d >= inf / 2) d = numeric_limits<weight_t<G>>::max();
  return {!success, move(dist)};
}
