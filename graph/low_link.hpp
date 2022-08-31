#pragma once
#include "graph.hpp"

// articulation points, bridges
template <class G>
auto low_link(const G& graph) {
  graph_trait<G> g(graph);
  vector<int> in(g.size()), low(g.size()), vs;
  vector<pair<int, int>> es;

  int t = 0;
  vector<char> done(g.size()), pushed(g.size());
  auto dfs = [&](auto&& f, int v, int p) -> void {
    done[v] = true, low[v] = in[v] = t++;
    int ch = 0;
    g.adj(v, [&](int u) {
      if (u == p) return;
      if (done[u])
        low[v] = min(low[v], in[u]);
      else {
        f(f, u, v), low[v] = min(low[v], low[u]);
        if (low[u] > in[v]) es.emplace_back(v, u);
        if (low[u] >= in[v] && p != -1 && !pushed[v])
          vs.push_back(v), pushed[v] = true;
        ch++;
      }
      if (p == -1 && ch > 1 && !pushed[v]) vs.push_back(v), pushed[v] = true;
    });
  };
  dfs(dfs, 0, -1);
  return make_pair(move(vs), move(es));
}
