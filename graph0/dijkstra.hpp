#pragma once
#include "graph0.hpp"

template <class G, class weight_t = weight_t<G>>
vector<weight_t> dijkstra(const G& graph, V<G> s, weight_t Inf = numeric_limits<weight_t>::max()) {
  graph_trait<G> g{graph};
  vector<weight_t> dist(g.size(), Inf);
  priority_queue<pair<weight_t, V<G>>, vector<pair<weight_t, V<G>>>, greater<>> togo;
  dist[g.id(s)] = 0, togo.emplace(0, s);
  while (!togo.empty()) {
    weight_t d; V<G> v;
    tie(d, v) = togo.top(), togo.pop();
    if (dist[g.id(v)] != d) continue;
    g.adj_w(v, [&](auto u, auto w) {
      if (dist[g.id(u)] > d + w) togo.emplace(dist[g.id(u)] = d + w, u);
    });
  }
  return dist;
}
