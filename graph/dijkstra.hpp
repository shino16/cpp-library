#pragma once
#include "graph.hpp"

template <class G, class Iter>
vector<W<G>> dijkstra(const G& graph, Iter s_it, Iter s_last) {
  graph_trait<G> g(graph);
  vector<W<G>> dist(g.size(), numeric_limits<W<G>>::max());
  priority_queue<pair<W<G>, int>, vector<pair<W<G>, int>>, greater<>> hp;
  while (s_it != s_last) hp.emplace(W<G>(0), *s_it), dist[*s_it++] = W<G>(0);
  while (!hp.empty()) {
    auto [w, v] = hp.top();
    hp.pop();
    if (w != dist[v]) continue;
    g.adj(v, [&](auto&& e) {
      if (dist[e.to()] > dist[v] + e.w())
        dist[e.to()] = dist[v] + e.w(), hp.emplace(dist[e.to()], e.to());
    });
  }
  return dist;
}

template <class G>
vector<W<G>> dijkstra(const G& graph, int s) {
  return dijkstra(graph, &s, &s + 1);
}
