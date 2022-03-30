#pragma once
#include "graph.hpp"

template <class G, class Fin, class Fout>
void dfs_all(const G& graph, Fin&& fin, Fout&& fout) {
  graph_trait<G> g(graph);
  vector<char> visited(g.size(), false);
  rep(s, g.size()) if (!visited[s]) {
    visited[s] = true;
    auto dfs_fn = [&](auto&& f, int v) {
      g.adj(v, [&](auto&& e) {
        if (!visited[e.to()])
          visited[e.to()] = true, fin(e, v), f(f, e.to()), fout(e, v);
      });
    };
    dfs_fn(dfs_fn, s);
  }
}

template <class G, class F>
void dfs_all(const G& graph, F&& f) {
  dfs_all(graph, f, [](auto&&...) {});
}
