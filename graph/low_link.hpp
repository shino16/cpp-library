#pragma once
#include "graph.hpp"

// articulation points, bridges
template <class G>
auto low_link(const G& graph) {
  graph_trait<G> g(graph);
  vector<int> in(g.size()), low(g.size()), vs;
  vector<pair<int, typename graph_trait<G>::edge_type>> es;

  int t = 0;
  vector<char> done(g.size()), pushed(g.size());
  auto dfs = [&](auto&& f, int v, int p) -> void {
    done[v] = true, low[v] = in[v] = t++;
    int ch = 0;
    g.adj(v, [&](auto e) {
      if (e.to() == p) return;
      if (done[e.to()])
        low[v] = min(low[v], in[e.to()]);
      else {
        f(f, e.to(), v), low[v] = min(low[v], low[e.to()]);
        if (low[e.to()] > in[v]) es.emplace_back(v, e.underlying());
        if (low[e.to()] >= in[v] && p != -1 && !pushed[v]) vs.push_back(v), pushed[v] = true;
        ch++;
      }
      if (p == -1 && ch > 1 && !pushed[v]) vs.push_back(v), pushed[v] = true;
    });
  };
  dfs(dfs, 0, -1);
  return make_pair(move(vs), move(es));
}
