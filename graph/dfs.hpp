#pragma once
#include "graph.hpp"

template <class G, class Fin, class Fout>
void dfs(G& graph, int s, Fin&& fin, Fout&& fout) {
  graph_trait<G> g(graph);
  vector<char> visited(g.size(), false);
  visited[s] = true;
  auto dfs_fn = [&](auto&& f, int v) {
    g.adj(v, [&](auto&& e) {
      if (!visited[e.to])
        visited[e.to] = true, fin(e, v), f(f, e.to), fout(e, v);
    });
  };
  dfs_fn(dfs_fn, s);
}

template <class G, class F>
void dfs(G& graph, int s, F&& f) {
  dfs(graph, s, f, [](auto&&, auto&&) {});
}

template <class G, class F>
void dfs_bottom_up(G& graph, int s, F&& f) {
  dfs(graph, s, [](auto&&, auto&&) {}, f);
}

template <class G, class F>
void dfs_ord(G& graph, int s, F&& f) {
  f(s, -1);
  dfs(graph, s, [&](int v, int p) { f(v, p); });
}

template <class G, class F>
void dfs_rev_ord(G& graph, int s, F&& f) {
  dfs_bottom_up(graph, s, [&](int v, int p) { f(v, p); });
  f(s, -1);
}
