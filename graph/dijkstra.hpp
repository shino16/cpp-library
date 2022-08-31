#pragma once
#include "graph.hpp"

template <class G, class Iter>
vector<weight_t<G>> dijkstra(const G& graph, Iter s_it, Iter s_last) {
  graph_trait<G> g(graph);
  vector<weight_t<G>> dist(g.size(), numeric_limits<weight_t<G>>::max());
  priority_queue<pair<weight_t<G>, int>, vector<pair<weight_t<G>, int>>, greater<>> hp;
  while (s_it != s_last) hp.emplace(weight_t<G>(0), *s_it), dist[*s_it++] = weight_t<G>(0);
  while (!hp.empty()) {
    auto [w, v] = hp.top();
    hp.pop();
    if (w != dist[v]) continue;
    g.adj(v, [&](auto&& e) {
      if (dist[e.to] > dist[v] + e.w())
        dist[e.to] = dist[v] + e.w(), hp.emplace(dist[e.to], e.to);
    });
  }
  return dist;
}

template <class G>
vector<weight_t<G>> dijkstra(const G& graph, int s) {
  return dijkstra(graph, &s, &s + 1);
}
