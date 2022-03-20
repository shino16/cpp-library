#pragma once
#include "graph0.hpp"

template <class G>
pair<vector<W<G>>, vector<V<G>>> bfs(const G& graph, V<G> s,
                                     W<G> Inf = numeric_limits<W<G>>::max(),
                                     V<G> sentinel = -1) {
  graph_trait<G> g{graph};
  vector<W<G>> dist(g.size(), Inf);
  vector<V<G>> togo;
  vector<V<G>> par(g.size(), sentinel);
  togo.reserve(g.size());
  auto itr = togo.begin();

  dist[g(s)] = W<G>(0);
  togo.push_back(s);

  while (itr != togo.end()) {
    V<G> v = *itr++;
    g.adj_w(v, [&](auto u, auto w) {
      if (dist[g(u)] == Inf)
        dist[g(u)] = dist[g(v)] + w, togo.push_back(u), par[g(u)] = v;
    });
  }
  return {dist, par};
}
