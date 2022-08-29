#pragma once
#include "graph/bellman_ford.hpp"
#include "graph/dijkstra.hpp"

template <class G>
class reduced_graph : public graph_trait<G> {
 public:
  reduced_graph(G& graph, vector<W<G>>& potential)
      : graph_trait<G>(graph), potential(potential) {}
  template <class F>
  void adj(int v, F&& f) const {
    graph_trait<G>::adj(v, [&](auto&& e) {
      W<G> reduced_cost = e.w() + potential[v] - potential[e.to];
      f(weighted_edge<W<G>>{e.to, reduced_cost});
    });
  }

 private:
  vector<W<G>>& potential;
};

// graph should be strongly connected
template <class G>
optional<vector<vector<W<G>>>> all_pairs_distances(G& graph) {
  const W<G> inf = numeric_limits<W<G>>::max();
  graph_trait<G> g(graph);
  vector<vector<W<G>>> dist(g.size());
  auto [fail, potential] = bellman_ford(graph, 0);
  bool reachable = count(all(potential), inf) == 0;
  if (fail || !reachable) return nullopt;

  reduced_graph<G> g2(graph, potential);

  dist[0] = potential;
  rep2(v, 1, g.size()) {
    dist[v] = dijkstra(g2, v);
    rep(u, g.size()) dist[v][u] =
        dist[v][u] == inf ? inf : dist[v][u] - potential[v] + potential[u];
  }
  return optional(move(dist));
}
