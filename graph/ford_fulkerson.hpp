#pragma once
#include "graph.hpp"
#include "math/sat.hpp"

template <class G>
vector<vector<W<G>>> ford_fulkerson(const G& graph) {
  const W<G> inf = numeric_limits<W<G>>::max();
  graph_trait<G> g(graph);
  vector<vector<W<G>>> res(g.size(), vector<W<G>>(g.size(), inf));
  rep(v, g.size()) {
    res[v][v] = W<G>(0);
    g.adj(v, [&](auto&& e) { res[v][e.to] = e.w(); });
  }
  rep(k, g.size()) rep(u, g.size()) rep(v, g.size())
    res[u][v] = min(res[u][v], sat_add(res[u][k], res[k][v]));
  rep(u, g.size()) rep(v, g.size())
    res[u][v] = res[u][v] >= inf / 2 ? inf : res[u][v];
  return res;
}
