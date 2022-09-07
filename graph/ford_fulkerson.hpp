#pragma once
#include "graph.hpp"
#include "arith/sat.hpp"

template <class G>
vector<vector<weight_t<G>>> ford_fulkerson(const G& graph) {
  const weight_t<G> inf = numeric_limits<weight_t<G>>::max();
  graph_trait<G> g(graph);
  vector<vector<weight_t<G>>> res(g.size(), vector<weight_t<G>>(g.size(), inf));
  rep(v, g.size()) {
    res[v][v] = weight_t<G>(0);
    g.adj(v, [&](auto&& e) { res[v][e.to] = e.w(); });
  }
  rep(k, g.size()) rep(u, g.size()) rep(v, g.size())
    res[u][v] = min(res[u][v], sat_add(res[u][k], res[k][v]));
  rep(u, g.size()) rep(v, g.size())
    res[u][v] = res[u][v] >= inf / 2 ? inf : res[u][v];
  return res;
}
