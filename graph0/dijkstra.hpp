#pragma once
#include "graph0.hpp"

template <class G, class W = W<G>>
vector<W> dijkstra(const G& graph, V<G> s, W Inf = numeric_limits<W>::max()) {
  graph_trait<G> g{graph};
  vector<W> dist(g.size(), Inf);
  priority_queue<pair<W, V<G>>, vector<pair<W, V<G>>>, greater<>> togo;
  dist[g.id(s)] = 0, togo.emplace(0, s);
  while (!togo.empty()) {
    W d; V<G> v;
    tie(d, v) = togo.top(), togo.pop();
    if (dist[g.id(v)] != d) continue;
    g.adj_w(v, [&](auto u, auto w) {
      if (dist[g.id(u)] > d + w) togo.emplace(dist[g.id(u)] = d + w, u);
    });
  }
  return dist;
}
