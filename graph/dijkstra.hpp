#pragma once
#include "graph.hpp"
#include "ds/heap.hpp"

template <class G, class Iter>
vector<weight_t<G>> dijkstra(
    const G& graph, Iter s_it, Iter s_last,
    weight_t<G> M = numeric_limits<weight_t<G>>::max()) {
  graph_trait<G> g(graph);
  vector<weight_t<G>> dist(g.size(), M);
  heap<weight_t<G>, greater<>> hp;
  while (s_it != s_last)
    hp.insert(*s_it, weight_t<G>(0)), dist[*s_it++] = weight_t<G>(0);
  while (!hp.empty()) {
    auto [w, v] = hp.pop();
    g.adj(v, [&, v = v](auto&& e) {
      if (dist[e.to] > dist[v] + e.w())
        hp.insert_or_modify(e.to, dist[e.to] = dist[v] + e.w());
    });
  }
  return dist;
}

template <class G>
vector<weight_t<G>> dijkstra(
    const G& graph, int s, weight_t<G> M = numeric_limits<weight_t<G>>::max()) {
  return dijkstra(graph, &s, &s + 1, M);
}
