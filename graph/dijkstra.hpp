#pragma once
#include "graph.hpp"

template <class G>
vector<W<G>> dijkstra(G& graph, int s) {
  graph_trait<G> g(graph);
  vector<W<G>> dist(g.size(), numeric_limits<W<G>>::max());
  priority_queue<pair<W<G>, int>, vector<pair<W<G>, int>>, greater<>> hp;
  hp.emplace(W<G>(0), s);
  dist[s] = W<G>(0);
  while (!hp.empty()) {
    auto [w, v] = move(hp.top());
    hp.pop();
    if (w != dist[v]) continue;
    g.adj(v, [&](auto&& e) {
      if (dist[e.to()] > dist[v] + e.w())
        dist[e.to()] = dist[v] + e.w(),
        hp.emplace(dist[e.to()], e.to());
    });
  }
  return dist;
}
