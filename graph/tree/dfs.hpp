#pragma once
#include "graph.hpp"

template <class G, class Fin, class Fout>
void dfs(const G& graph, int s, Fin&& fin, Fout&& fout) {
  graph_trait<G> g(graph);
  auto dfs_fn = [&](auto&& f, int v, int p) {
    g.adj(v, [&](auto&& e) {
      if (e.to() != p)
        fin(e, v), f(f, e.to(), v), fout(e, v);
    });
  };
  dfs_fn(dfs_fn, s, -1);
}

template <class G, class F>
void dfs(const G& graph, int s, F&& f) {
  dfs(graph, s, f, [](auto&&, auto&&) {});
}

template <class G, class F>
void dfs_bottom_up(const G& graph, int s, F&& f) {
  dfs(graph, s, [](auto&&, auto&&) {}, f);
}

template <class G, class F>
void dfs_ord(const G& graph, int s, F&& f) {
  f(s, -1);
  dfs(graph, s, [&](int v, int p) { f(v, p); });
}

template <class G, class F>
void dfs_rev_ord(const G& graph, int s, F&& f) {
  dfs_bottom_up(graph, s, [&](int v, int p) { f(v, p); });
  f(s, -1);
}
